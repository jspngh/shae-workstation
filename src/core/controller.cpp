#include "controller.h"

Controller::Controller(MainWindow *window, QObject *parent) :
    QThread(parent)
{
    mainWindow = window;

    drones = new QSet<Drone*>();
}

Controller::~Controller()
{
}

void Controller::run()
{
    createPersistence();
    createCommunication();
    createDrone();
    createDetectionController();
    createMediator();
}

void Controller::createMediator()
{
    mediator = new Mediator(mainWindow);
    mediator->moveToThread(&mediatorThread);
}

void Controller::createCommunication()
{
    communication = new Communication();
    communication->moveToThread(&communicationThread);
}

void Controller::createDetectionController()
{
    detectionController = new DetectionController();
    detectionController->moveToThread(&detectorThread);
}

//! this should ideally be done by the communication module
void Controller::createDrone()
{
    drones->insert(new Drone());
}

void Controller::createPersistence()
{
    persistence = new Persistence();
    persistence->moveToThread(&persistenceThread);
}

