
#include "controller.h"
#include <QUuid>

Controller::Controller(MainWindow *window, QObject *p)
    : QObject(p)
{
    mainWindow = window;

    search = new Search();

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

    drones->append(new DroneModule(6330, 5502, "127.0.0.1", 0.0001));

    // real drone: 10.1.1.10:6330
    // simulator: 127.0.0.1:6330

    // create controllers
    detectionController = new DetectionController(mediator);
    //persistenceController = new Persistence(mediator);
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
    // configure every component with the controller
    mainWindow->getConfigWidget()->setController(this);
    pathLogicController->setController(this);
    // set every component in a different thread
    // NOTE: all the drones are placed in the same thread (TODO: make thread for every drone)

    // detectionController->moveToThread(&detectorThread);
    // persistenceController->moveToThread(&persistenceThread);
    pathLogicController->moveToThread(&pathLogicThread);
    for (int i = 0; i < drones->size(); i++)
        (*drones)[i]->moveToThread(&droneThread);
    pathLogicThread.start();
    //TODO: wait until the first waypoint has been reached
    // for now, this is a simple sleep construction
    QThread::sleep(5);
    for (int i = 0; i < drones->size(); i++) {
        (*drones)[i]->setController(this);
        (*drones)[i]->getStream();
    }
    // allow the stream to buffer
    QThread::sleep(5);
    // start all the threads
    detectionController->moveToThread(&detectorThread);
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

