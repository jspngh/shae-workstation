#ifndef OVERVIEWDRONEITEM_H
#define OVERVIEWDRONEITEM_H

#include <QWidget>
#include <QGeoCoordinate>
#include <QDateTime>
#include <QDebug>
#include <QTimer>
#include "communication/dronemodule.h"
#include "models/dronestatus.h"


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

private:
    void updateSearchedArea(DroneStatus s);

    //! Calculate the vision width in meters.
    //! This quantity is derived from the vision width in degrees.
    //! The value depends on the location of the drone.
    void calculateVisionWidthMeters();

public slots:
    void setDroneNr(uint number);
    void setBatteryLevel(double level);
    void setSearchedArea(double area);
    void setStatus(QString status); //! possible values are 'taking off', 'flying', 'landed'
    void setConnectivity(QString level); //! possible values are 'good', 'poor', 'bad', 'no signal'
    void updateStatus(DroneStatus status);
    void incrementPeopleLocated();
    void updateConnectivity();

private:
    Ui::OverviewDroneItem *ui;
    int locatedPeople;
    double visionWidthMeters;
    double visionWidthDegrees;
    double searchedArea;
    DroneStatus lastStatus;
    bool receivedStatus;
    QTimer *timer;
};

#endif // OVERVIEWDRONEITEM_H

