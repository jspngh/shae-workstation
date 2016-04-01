
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
    drones->append(new DroneModule(6330, 5502, "127.0.0.1", QString("rtp://127.0.0.1:5000"),  0.0001));
    // real drone: 10.1.1.10:6330
    // simulator: 127.0.0.1:6331


    // real drone: 10.1.1.10:6330
    // simulator: 127.0.0.1:6330

    // create controllers
    detectionController = new DetectionController(search);
    videoController = new VideoController();
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
    //TODO: wait until the first waypoint has been reached
    // for now, this is a simple sleep construction
    d->setController(this);
    d->getStream();
    QString streamPath = d->getDrone().getStreamPath();
    VideoSequence sequence  = videoController->onStartStream(streamPath);
    cv::VideoCapture capture = cv::VideoCapture(sequence.getPath().toStdString());
    // allow the stream to buffer
    detectionController->setSequence(capture);
    // start all the threads
    detectionController->start();
    // persistenceThread.start();
}



/*****************
 *    Getters
 *****************/

Mediator *Controller::getMediator() const
{
    return mediator;
}

QList<DroneModule *> *Controller::getDrones() const
{
    return drones;
}

Search *Controller::getSearch() const
{
    return search;
}

QString Controller::getWorkstationIP() const
{
    return workstationIP;
}

