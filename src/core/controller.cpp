#include "controller.h"
#include <QUuid>

Controller::Controller(MainWindow *window, QObject *p)
    : QObject(p)
{
    mainWindow = window;

    // create the mediator. Note: the same mediator object must be shared among all the components!
    mediator = new Mediator();

    // create drones
    // TODO: drone info (IP, port, etc) should be set elsewhere
    drones = new QList<Drone *>();
    drones->append(new Drone(6331, "127.0.0.1", 0.0001));


    // create controllers
    //detectionController = new DetectionController(mediator);
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
    mainWindow->getConfigWidget()->setMediator(mediator);
    mainWindow->getOverviewWidget()->setMediator(mediator);
    pathLogicController->setMediator(mediator);
    for (int i = 0; i < drones->size(); i++)
        (*drones)[i]->setController(this);

    // set every component in a different thread
    // NOTE: all the drones are placed in the same thread (TODO: make thread for every drone)

    // detectionController->moveToThread(&detectorThread);
    // persistenceController->moveToThread(&persistenceThread);
    pathLogicController->moveToThread(&pathLogicThread);
    for (int i = 0; i < drones->size(); i++)
        (*drones)[i]->moveToThread(&droneThread);

    // start all the threads
    // detectorThread.start();
    // persistenceThread.start();
    droneThread.start();
    pathLogicThread.start();
}

/*****************
 *    Getters
 *****************/

Mediator *Controller::getMediator() const
{
    return mediator;
}

QList<Drone *> *Controller::getDrones() const
{
    return drones;
}

