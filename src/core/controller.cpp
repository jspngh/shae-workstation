#include "controller.h"

Controller::Controller(MainWindow *window, QObject *p)
    : QObject(p)
{
    mainWindow = window;

    // create the mediator. Note: the same mediator object must be shared among all the components!
    mediator = new Mediator();

    workstationIP = initWorkstationIP();

    drones = new QList<DroneModule*>();

    // create controllers
    pathLogicController = new SimplePathAlgorithm();
    persistenceController = new PersistenceController();

    startListingForDrones();
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
    if(detectionController)
        delete detectionController;
}

void Controller::init()
{
    // configure every component with the mediator
    pathLogicController->setMediator(mediator);
    mainWindow->getConfigWidget()->setMediator(mediator);
    mainWindow->getOverviewWidget()->setMediator(mediator);
    persistenceController->setMediator(mediator);

    // place every component in a different thread
    persistenceController->moveToThread(&persistenceThread);
    pathLogicController->moveToThread(&pathLogicThread);

    // start all the threads
    persistenceThread.start();
    pathLogicThread.start();
    droneThread.start();

    //add slot for search
    getMediator()->addSlot(this, SLOT(onSearchEmitted(Search *)), QString("startSearch(Search*)"));
}

 void Controller::initStream(DroneModule* d)
{
    qDebug() << "Controller: stream started at workstation";
    VideoSequence sequence  = d->getVideoController()->onStartStream(d->getDrone());

    detectionController = new DetectionController(search, d, persistenceController);
    detectionController->setMediator(mediator);

    qDebug() << "Controller: starting to save stream";
    // allow the stream to buffer
    //WARNING VideoCapture needs to be performed on the main thread!
    cv::VideoCapture capture;
    capture.open(sequence.getPath().toStdString().c_str());
    while(!capture.isOpened()){
        QThread::sleep(1);
        qDebug()<< "stream file not yet open, waiting";
    }
    qDebug() << "Controller: stream file has been succesfully opened";
    // allow the stream to buffer
    detectionController->setSequence(capture);


    // allow the stream to bufer for a second
    qDebug() << "Controller: starting detectioncontroller";
    detectionController->start();

}

QString Controller::initWorkstationIP()
{
    foreach(const QHostAddress & address, QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol
                && address != QHostAddress(QHostAddress::LocalHost))
            return address.toString();
    }
    return QString();
}

void Controller::stopStream(DroneModule* d)
{
    d->getVideoController()->onStopStream(d->getDrone());
    d->stopStream();
    detectionController->streamFinished();
}

void Controller::onSearchEmitted(Search* s){
    qDebug() << "Controller::saved search";
    search = s;
}

void Controller::startListingForDrones()
{
    udpSocket  = new QUdpSocket(this);
    host  = new QHostAddress("127.0.0.1");
    udpSocket->bind(*host, 4849);
    connect(udpSocket,SIGNAL(readyRead()),this,SLOT(readPendingDatagrams()));
}


void Controller::readPendingDatagrams()
{
    while (udpSocket->hasPendingDatagrams()) {
        QByteArray helloRaw;
        QHostAddress sender;
        quint16 senderPort;

        helloRaw.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(helloRaw.data(), helloRaw.size(), &sender, &senderPort);

        processHelloMessage(helloRaw);
    }
}

void Controller::processHelloMessage(QByteArray helloRaw)
{
    HelloMessage hello = HelloMessage::parse(helloRaw);

    QString ip = hello.getDroneIp();
    QString strFile =  hello.getStreamFile();
    int cmdPort = hello.getCommandsPort();
    int strPort = hello.getStreamPort();
    double vision = hello.getVisionWidth();

    DroneModule *drone = receivedHelloFrom(ip);
    if(drone == nullptr) {
        // first time that the drone with this IP has sent a Hello message
        drone = new DroneModule(cmdPort, strPort, ip, controllerIp, workstationIP, strFile, vision);
        drone->setMediator(mediator);
        drone->moveToThread(&droneThread);
        drones->append(drone);
    }

    drone->requestStatus();
}

 DroneModule *Controller::receivedHelloFrom(QString ip)
 {
    for(int i = 0; i < drones->size(); i++){
        if((*drones)[i]->getDroneIp() == ip)
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


void Controller::setDrones(QList<DroneModule *>* list)
{
    drones = list;
}

Search *Controller::getSearch() const
{
    return search;
}

QString Controller::getWorkstationIP() const
{
    return workstationIP;
}

DetectionController *Controller::getDetectionController() const
{
    return detectionController;
}
