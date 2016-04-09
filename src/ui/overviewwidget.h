#ifndef OVERVIEWWIDGET_H
#define OVERVIEWWIDGET_H

#include <QListWidgetItem>
#include <QMap>
#include <QMMarker.h>
#include <QMMapView.h>
#include <QUuid>
#include <QWidget>
#include "overviewdroneitem.h"
#include "communication/dronemodule.h"
#include "core/mediator.h"
#include "models/search.h"

namespace Ui {
class OverviewWidget;
}

class OverviewWidget : public QWidget
{
    Q_OBJECT

public:
    explicit OverviewWidget(QWidget *parent = 0);
    ~OverviewWidget();
    void setMediator(Mediator *mediator);

private:
    QMMapView *mapView;
    bool mapViewLoaded;
    Ui::OverviewWidget *ui;
    Search *search;
    Mediator *mediator;
    QMap<QUuid, OverviewDroneItem*> mapIdListItem;

private slots:
    void exportSearchButtonPush();
    void onSearchStarted(Search *s);
    void onHeartBeatReceived(DroneStatus heartbeat);
    void fillDroneList();
    void updateDroneList(DroneStatus s);
    void onMapLoaded();
    void onMapFailedToLoad();
};

#endif // OVERVIEWWIDGET_H
