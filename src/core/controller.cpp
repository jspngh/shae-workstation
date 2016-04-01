
#include "controller.h"
#include <QUuid>


Controller::Controller(MainWindow *window, QObject *p)
    : QObject(p)
{
    mainWindow = window;

    //configure the search (should be done through the interface)
    search = new Search();
    search->setHeight(3);
    search->setGimbalAngle(65);
    search->setFpsProcessing(2);

    // create the mediator. Note: the same mediator object must be shared among all the components!
    mediator = new Mediator();


    //set workstationIP
    foreach (const QHostAddress &address, QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != QHostAddress(QHostAddress::LocalHost))
            workstationIP = address.toString();
    }
    //TODO: delete override
    workstationIP = "127.0.0.1";



    // create drones
    // TODO: drone info (IP, port, etc) should be set elsewhere

    drones = new QList<DroneModule *>();
    //drones->append(new DroneModule(6330, 5502, "10.1.1.1", QString("dependencies/sololink.sdp"),  0.0001));
    //drones->append(new DroneModule(6330, 5502, "127.0.0.1", QString("rtp://127.0.0.1:5000"),  0.0001));
    // real drone: 10.1.1.10:6330
    // simulator: 127.0.0.1:6331


    // real drone: 10.1.1.10:6330
    // simulator: 127.0.0.1:6330

    // create controllers
    detectionController = new DetectionController(search);
    pathLogicController = new SimplePathAlgorithm();
}

Controller::~Controller()
{
    // stop all the threads in order to safely delete them afterwards
    droneThread.quit();
    droneThread.wait();
    pathLogicThread.quit();
    pathLogicThread.wait();
    // persistenceThread.quit();
    // persistenceThread.wait();

    delete mediator;

    //TODO:what if no waypoints were assigned?
    //delete search;

    // special Qt function to delete QList of pointers
    qDeleteAll(drones->begin(), drones->end());
    drones->clear();

    delete drones;

    // delete detectionController;
    // delete persistenceController;
    delete pathLogicController;
}

void Controller::init()
{
    // init the controller for single drone use.
    DroneModule *d = drones->first();

    // configure every component with the controller
    mainWindow->getConfigWidget()->setController(this);
    pathLogicController->setController(this);
    // set every component in a different thread
    // NOTE: all the drones are placed in the same thread (TODO: make thread for every drone)

    // detectionController->moveToThread(&detectorThread);
    // persistenceController->moveToThread(&persistenceThread);
    pathLogicController->moveToThread(&pathLogicThread);
    d->moveToThread(&droneThread);
    d->setController(this);
}


void Controller::initStream(DroneModule* d)
{

    d->getStream();
    QString streamPath = d->getDrone()->getStreamPath();
    qDebug() << "Controller: stream started at drone";
    VideoSequence sequence  = d->getVideoController()->onStartStream(streamPath);
    qDebug() << "Controller: starting to save stream";
    // allow the stream to buffer

    QThread::sleep(1);
    //WARNING VideoCapture needs to be performed on the main thread!
    cv::VideoCapture capture = cv::VideoCapture(sequence.getPath().toStdString());

    if(true){
        qDebug() << "Controller: stream file has been succesfully opened";
        // allow the stream to buffer
        detectionController->setSequence(capture);
        // start all the threads
        // allow the stream to bufer for a second
        QThread::sleep(1);
        detectionController->start();
    }

}

void Controller::stopStream(DroneModule* d)
{
    d->getVideoController()->onStopStream();
    detectionController->streamFinished();
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

