#include "overviewdroneitem.h"
#include "ui_overviewdroneitem.h"

OverviewDroneItem::OverviewDroneItem(DroneModule *drone, uint number, QWidget *parent)
    : QWidget(parent),
      ui(new Ui::OverviewDroneItem),
      locatedPeople(0)
{
    ui->setupUi(this);

    setDroneNr(number);

    connect(ui->emergencyButton, SIGNAL(clicked()), drone, SLOT(emergencyLanding()));
    connect(ui->haltButton, SIGNAL(clicked()), drone, SLOT(stopFlight()));
    connect(ui->returnHomeButton, SIGNAL(clicked()), drone, SLOT(returnToHome()));
}

OverviewDroneItem::~OverviewDroneItem()
{
    delete ui;
}

void OverviewDroneItem::setDroneNr(uint number)
{
    ui->header->setText(
        QString("Drone #%1").arg(number)
    );
}

void OverviewDroneItem::updateStatus(DroneStatus status)
{
    double batteryLevel = status.getBatteryLevel();
    if(batteryLevel != -1)
        ui->batteryValue->setText(QString::number(batteryLevel) + "%");
}

int OverviewDroneItem::getPeopleLocated()
{
    return locatedPeople;
}

void OverviewDroneItem::incrementPeopleLocated()
{
    locatedPeople++;
    ui->locatedPeopleValue->setText(QString::number(locatedPeople));
}

