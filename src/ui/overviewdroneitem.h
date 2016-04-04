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
    explicit OverviewDroneItem(DroneModule *drone, QWidget *parent = 0);
    ~OverviewDroneItem();

private:
    Ui::OverviewDroneItem *ui;
};

#endif // OVERVIEWDRONEITEM_H

