#include "overviewdroneitem.h"
#include "ui_overviewdroneitem.h"

OverviewDroneItem::OverviewDroneItem(DroneModule *drone, QWidget *parent)
    : QWidget(parent),
      ui(new Ui::OverviewDroneItem)
{
}

OverviewDroneItem::~OverviewDroneItem()
{
}

