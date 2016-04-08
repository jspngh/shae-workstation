#include "overviewdroneitem.h"
#include "ui_overviewdroneitem.h"

OverviewDroneItem::OverviewDroneItem(DroneModule *drone, uint number, QWidget *parent)
    : QWidget(parent),
      ui(new Ui::OverviewDroneItem)
{
    ui->setupUi(this);
    setDroneNr(number);
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
