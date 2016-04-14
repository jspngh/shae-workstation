#ifndef OVERVIEWDRONEITEM_H
#define OVERVIEWDRONEITEM_H

#include <QWidget>
#include "communication/dronemodule.h"

namespace Ui {
class OverviewDroneItem;
}

class OverviewDroneItem : public QWidget
{
    Q_OBJECT

public:
    explicit OverviewDroneItem(DroneModule *drone, uint number, QWidget *parent = 0);
    ~OverviewDroneItem();
    int getPeopleLocated();

public slots:
    void setDroneNr(uint number);
    void updateStatus(DroneStatus status);
    void incrementPeopleLocated();

private:
    Ui::OverviewDroneItem *ui;
    int locatedPeople;
};

#endif // OVERVIEWDRONEITEM_H

