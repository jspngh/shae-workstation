#include "mediator.h"

Mediator::Mediator(QObject *parent) :
    QObject(parent)
{
    this->drones = new QSet<Drone*>();
}

Mediator::~Mediator()
{
    delete this->drones;
}

void Mediator::setWelcomeWidget(Ui::WelcomeWidget *welcomeWidget)
{
    this->welcomeWidget = welcomeWidget;
}

void Mediator::setConfigWidget(Ui::ConfigWidget *configWidget)
{
    this->configWidget = configWidget;
}

void Mediator::setOverviewWidget(Ui::OverviewWidget *overviewWidget)
{
    this->overviewWidget = overviewWidget;
}

void Mediator::addDrone(Drone *drone)
{
    this->drones->insert(drone);
}

void Mediator::removeDrone(Drone *drone)
{
    this->drones->remove(drone);
}


