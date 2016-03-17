#ifndef DRONESTATUS_H
#define DRONESTATUS_H
#include <QTime>
#include <QGeoCoordinate>

class DroneStatus
{
public:
    DroneStatus();

private:
    //contains long, lat and alt
    QGeoCoordinate position;
    //orientation (0-360 degrees)
    double orientation;
    double gimballAngle;
    double speed;
    double batteryLevel;
    int droneState;
    QTime timestampDrone;
    QTime timestampWorkstation;
};

#endif // DRONESTATUS_H
