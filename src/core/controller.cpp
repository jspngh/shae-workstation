#include "controller.h"
#include <QUuid>

Controller::Controller(MainWindow *window, QObject *parent) :
    QThread(parent)
{
    mainWindow = window;

    drones = new QSet<Drone *>();
}

Controller::~Controller()
{
}

void Controller::run()
{
    createMediator();
    createPersistence();
    createDrone();
    createDetectionController();
}

void Controller::createMediator()
{
    mediator = new Mediator();
    mediator->moveToThread(&mediatorThread);
    mainWindow->setMediator(mediator);
}

void Controller::createDetectionController()
{
    detectionController = new DetectionController(mediator);
    detectionController->moveToThread(&detectorThread);
}

//! this should ideally be done by the communication module
void Controller::createDrone()
{
    QUuid droneId = QUuid::createUuid();
    Drone *drone = new Drone(mediator, droneId, 6331, "127.0.0.1", 0.0001);
    drones->insert(drone);
}

void Controller::createPersistence()
{
    persistence = new Persistence(mediator);
    persistence->moveToThread(&persistenceThread);
}

