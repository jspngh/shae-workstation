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
    mainWindow->getConfigWidget()->setMediator(mediator);
    mainWindow->getOverviewWidget()->setMediator(mediator);
    mainWindow->getWelcomeWidget()->setMediator(mediator);
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

    QProcess *proc = new QProcess;
    QString name = "/bin/bash";
    QStringList arg;
    arg << "-c" ;

    QFile file(":/scripts/reset_services.sh");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "script file not found / failed to load";
        return;
    } else {
        qDebug() << "resetting services";
    }

    arg << file.readAll();
    proc->start(name, arg);
    proc->waitForFinished(-1);
    proc->close();
}

void Controller::onSearchEmitted(Search *s)
{
    search = s;
    QGeoCoordinate home = drones->front()->getLastReceivedDroneStatus().getCurrentLocation();
    if(s->getArea()->type() == QGeoShape::RectangleType)
        pathLogicController = new SimplePathAlgorithm(home);
    else
        pathLogicController = new PolygonPathAlgorithm(home);

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
 *    Getters
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


