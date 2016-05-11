#include <QProcess>
#include "controller.h"

Controller::Controller(MainWindow *window, QObject *p)
    : QObject(p)
{
    mainWindow = window;

    // create the mediator. Note: the same mediator object must be shared among all the components!
    mediator = new Mediator();

    retrieveWorkstationIpAndBroadcast();
    qDebug() << workstationBroadcastIp;
    qDebug() << workstationIp;

    drones = new QList<DroneModule *>();

    // create controllers
    persistenceController = new PersistenceController();

    startListeningForDrones();

    // add signal/slot
    mediator->addSlot(this, SLOT(onSearchEmitted(Search *)), QString("startSearch(Search*)"));
    mediator->addSignal(this, SIGNAL(droneSetupFailed()), QString("droneSetupFailed()"));
    mediator->addSlot(this, SLOT(onResetServicesClicked()), QString("resetServicesClicked()"));
}

Controller::~Controller()
{
    // stop all the threads in order to safely delete them afterwards
    droneThread.quit();
    droneThread.wait();
    pathLogicThread.quit();
    pathLogicThread.wait();
    persistenceThread.quit();
    persistenceThread.wait();

    // delete the mediator and the search object
    delete mediator;
    // special Qt function to delete QList of pointers
    qDeleteAll(drones->begin(), drones->end());
    drones->clear();

    // delete persistenceController;
    delete pathLogicController;
}

void Controller::init()
{
    // configure every component with the mediator

    //pathLogicController->setMediator(mediator);
    mainWindow->setMediator(mediator);
    persistenceController->setMediator(mediator);

    // place every component in a different thread
    persistenceController->moveToThread(&persistenceThread);

    // start all the threads
    persistenceThread.start();
    pathLogicThread.start();
    droneThread.start();
}

void Controller::retrieveWorkstationIpAndBroadcast()
{
    foreach (const QNetworkInterface &iface, QNetworkInterface::allInterfaces()) {
        foreach (const QNetworkAddressEntry &entry, iface.addressEntries()) {
            QHostAddress address = entry.ip();
            if (address.protocol() == QAbstractSocket::IPv4Protocol
                    && address != QHostAddress(QHostAddress::LocalHost)){
                workstationIp = entry.ip().toString();
                workstationBroadcastIp = entry.broadcast().toString();
            }
        }
    }
}

void Controller::onResetServicesClicked()
{
    QString configFolder = QStandardPaths::writableLocation(QStandardPaths::DataLocation);
    QString rsaFileName = "shae_rsa";
    QString scriptFileName = "reset_services.sh";

    // create folder if not available
    QDir(QDir::root()).mkpath(configFolder);

    if (!configFolder.endsWith(QDir::separator()))
        configFolder.append(QDir::separator());

    QString keyPath = configFolder + rsaFileName;
    QString scriptPath = configFolder + scriptFileName;
    QFile rsaKey(keyPath);
    QFile resetScript(scriptPath);

    // if the file already exists nothing needs to be done anymore
    // in general this function only needs to copy the file once, the first the time the application runs
    if (!rsaKey.exists()) {
        QFile srcFile(":/scripts/shae_rsa");
        srcFile.open(QIODevice::ReadOnly);
        QTextStream in(&srcFile);
        rsaKey.open(QIODevice::WriteOnly);
        QTextStream out(&rsaKey);
        out << in.readAll();

        /* Close the files */
        rsaKey.close();
        srcFile.close();

        /* Set correct permissions */
        rsaKey.setPermissions(QFile::ReadOwner);
    }
    if (!resetScript.exists()) {
        QFile scriptSrcFile(":/scripts/reset_services.sh");
        scriptSrcFile.open(QIODevice::ReadOnly);
        QTextStream in(&scriptSrcFile);
        resetScript.open(QIODevice::WriteOnly);
        QTextStream out(&resetScript);
        out << in.readAll();

        /* Close the files */
        resetScript.close();
        scriptSrcFile.close();

        /* Set correct permissions */
        resetScript.setPermissions(QFile::ExeOwner | QFile::ReadOwner | QFile::WriteOwner);
    }

    QProcess *proc = new QProcess();
    QStringList arg;
    arg << keyPath;
    QMessageBox msgBox;
    msgBox.setText("The drone services are resetting.");
    proc->start(scriptPath, arg);
    qDebug() << "resetting services";
    msgBox.showMaximized();
    msgBox.exec();
    proc->waitForFinished(-1);
    proc->close();
    msgBox.close();
}

void Controller::onSearchEmitted(Search *s)
{
    search = s;
    if(s->getArea()->type() == QGeoShape::RectangleType)
        pathLogicController = new SimplePathAlgorithm();
    else
        pathLogicController = new PolygonPathAlgorithm();

    pathLogicController->moveToThread(&pathLogicThread);
    pathLogicController->setMediator(mediator);
    pathLogicController->startSearch(s);
}

int Controller::numDronesConnected()
{
    return drones->size();
}

void Controller::startListeningForDrones()
{
    udpSocketLan  = new QUdpSocket(this);
    host  = new QHostAddress(workstationBroadcastIp);
    udpSocketLan->bind(*host, helloPort);
    connect(udpSocketLan, SIGNAL(readyRead()), this, SLOT(readPendingDatagrams()));

    udpSocketLo  = new QUdpSocket(this);
    udpSocketLo->bind(QHostAddress("127.0.0.1"), helloPort);
    connect(udpSocketLo, SIGNAL(readyRead()), this, SLOT(readPendingDatagrams()));
}

void Controller::readPendingDatagrams()
{
    QByteArray helloRaw;
    QHostAddress sender;
    quint16 senderPort;

    while (udpSocketLan->hasPendingDatagrams()) {
        qDebug() << "receivedHello from LAN";
        helloRaw.resize(udpSocketLan->pendingDatagramSize());
        udpSocketLan->readDatagram(helloRaw.data(), helloRaw.size(), &sender, &senderPort);
        processHelloMessage(helloRaw);
    }

    while (udpSocketLo->hasPendingDatagrams()) {
        qDebug() << "receivedHello from LocalHost";
        helloRaw.resize(udpSocketLo->pendingDatagramSize());
        udpSocketLo->readDatagram(helloRaw.data(), helloRaw.size(), &sender, &senderPort);
        processHelloMessage(helloRaw);
    }
}

void Controller::processHelloMessage(QByteArray helloRaw)
{
    HelloMessage hello = HelloMessage::parse(helloRaw);
    // first check if we received an empty HelloMessage
    // this indicates failure at the side of the drone
    QString ip = hello.getDroneIp();
    if (ip.isEmpty() || ip.isNull()) {
        emit(droneSetupFailed()); // emit signal indicating failure
    } else {
        QString strFile = hello.getStreamFile();
        QString ctrIp = hello.getControllerIp();
        int cmdPort = hello.getCommandsPort();
        int strPort = hello.getStreamPort();
        double vision = hello.getVisionWidth();

        DroneModule *drone = receivedHelloFrom(ip);
        if (drone == nullptr) {
            // first time that the drone with this IP has sent a Hello message
            drone = new DroneModule(cmdPort, strPort, ip, ctrIp, workstationIp, strFile, vision, true);
            qDebug() << "created new  drone with ID: " << drone->getGuid().toString();
            drone->setPersistenceController(persistenceController);
            drone = configureDrone(drone);
        }
        drone->requestStatus();
    }
}

DroneModule *Controller::configureDrone(DroneModule *drone)
{
    qDebug() << "A new drone with ip " + drone->getDroneIp() + " is connected to the system.";
    drones->append(drone);
    drone->setMediator(mediator);
    drone->moveToThread(&droneThread);
    if (!oneStream) {
        // make sure that a stream is only requested once (even if there are multiple drones)
        drone->getStreamConnection();
        oneStream = true;
    }

    return drone;
}

DroneModule *Controller::receivedHelloFrom(QString ip)
{
    for (int i = 0; i < drones->size(); i++) {
        if ((*drones)[i]->getDroneIp() == ip)
            return (*drones)[i];
    }
    return nullptr;
}

/*****************
 *    Getters    *
 *****************/

Mediator *Controller::getMediator() const
{
    return mediator;
}

QList<DroneModule *> *Controller::getDrones()
{
    return drones;
}

void Controller::setDrones(QList<DroneModule *> *list)
{
    drones = list;
}

Search *Controller::getSearch() const
{
    return search;
}

QString Controller::getWorkstationIP() const
{
    return workstationIp;
}
