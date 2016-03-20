#include "controller.h"
#include <QUuid>

Controller::Controller(MainWindow *window) :
{
    mainWindow = window;

    search = new Search();

    // create the mediator. Note: the same mediator object must be shared among all the components!
    mediator = new Mediator();

    // create drones
    // TODO: drone info (IP, port, etc) should be set elsewhere
    drones = new QList<Drone>();
    QUuid droneId = QUuid::createUuid();
    drones->append(Drone(mediator, droneId, 6331, "127.0.0.1", 0.0001));

    // create controllers
    detectionController = new DetectionController(mediator);
    persistenceController = new Persistence(mediator);
    pathLogicController = new SimplePathAlgorithm();

}

Controller::~Controller()
{
    // TODO: stop all the threads
    delete mediator;
    delete search;
    delete drones;
    delete detectionController;
    delete persistenceController;
    delete pathLogicController;
}

void Controller::init()
{
    detectionController->moveToThread(&detectorThread);
    persistenceController->moveToThread(&persistenceThread);
    pathLogicController->moveToThread(&pathLogicThread);

    detectorThread.start();
    persistenceController.start();
    pathLogicController.start();

    mainWindow->getConfigWidget()->setController(this);
}

/*****************
 *    Getters
 *****************/

Mediator *Controller::getMediator() const
{
    return mediator;
}

QList<Drone> *Controller::getDrones() const
{
    return drones;
}

Search *Controller::getSearch() const
{
    return search;
}

