#ifndef OVERVIEWWIDGET_H
#define OVERVIEWWIDGET_H

#include <QListWidgetItem>
#include <QMap>
#include <QtMath>
#include <QMMarker.h>
#include <QMMapView.h>
#include <QUuid>
#include <QWidget>
#include "overviewdroneitem.h"
#include "overviewsearchitem.h"
#include "communication/dronemodule.h"
#include "core/mediator.h"
#include "models/detectionresult.h"
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
    Ui::OverviewWidget *ui;
    QMMapView *mapView;
    bool mapViewLoaded;
    OverviewSearchItem *searchDetails;

    Search *search;
    Mediator *mediator;
    QMap<QUuid, OverviewDroneItem *> mapIdListItem;

private slots:
    void exportSearchButtonPush();
    void onSearchStarted(Search *s);
    void onHeartBeatReceived(DroneStatus heartbeat);
    void onNewDetection(QUuid droneId, DetectionResult result);
    void fillDroneList();
    void updateDroneList(DroneStatus s);
    void onMapLoaded();
    void onMapFailedToLoad();
signals:
    void  printDetectionResultXML(QString);
    void  printDetectionResultTXT(QString);
};

#endif // OVERVIEWWIDGET_H
