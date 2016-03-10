#include "controller.h"

Controller::Controller(QObject *parent) :
    QObject(parent)
{
    createCommunication();
    createDetection();
    createPersistence();
    createMediator();
}

Controller::~Controller()
{
}

void Controller::setUiWidgets(MainWindow *window,
                              WelcomeWidget *welcomeWidget,
                              ConfigWidget *configWidget,
                              OverviewWidget *overviewWidget)
{
    mediator->setWelcomeWidget(welcomeWidget);
    mediator->setConfigWidget(configWidget);
    mediator->setOverviewWidget(overviewWidget);
}

void Controller::createMediator()
{
    this->mediator = new Mediator(this);
    this->mediator->moveToThread(this->mediatorThread);

    /* this->mediator->setCommunication(communication); */
    /* this->mediator->setDetection(communication); */
    /* this->mediator->setMediator(communication); */
}

void Controller::createCommunication()
{
    this->communication = new Communication(this);
    this->communication->moveToThread(this->communicationThread);
}

void Controller::createDetection()
{
}

void Controller::createPersistence()
{
}


