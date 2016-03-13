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
    createDetection();
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

void Controller::createDetection()
{
}

//! this should ideally be done by the communication module
void Controller::createDrone()
{
    drones->insert(new Drone());
}

void Controller::createPersistence()
{
}

