#ifndef OVERVIEWDRONEITEM_H
#define OVERVIEWDRONEITEM_H

#include <QWidget>
#include <QGeoCoordinate>
#include <QDateTime>
#include <QDebug>
#include <QTimer>
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
    void setBatteryLevel(double level);
    void setSearchedArea(double area);
    void setConnectivity(QString level);
    void updateStatus(DroneStatus status);
    void incrementPeopleLocated();
    void checkConnectivity();

private:
    Ui::OverviewDroneItem *ui;
    int locatedPeople;
    double visionWidthMeters;
    double visionWidthDegrees;
    double searchedArea;
    QGeoCoordinate lastLocation;
    bool hasLocation;
    QDateTime lastTimestamp;
    QTimer *timer;
};

#endif // OVERVIEWDRONEITEM_H

