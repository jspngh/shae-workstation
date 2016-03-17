#ifndef DRONESTATUS_H
#define DRONESTATUS_H
#include <QString>
#include <QTime>
#include <QGeoCoordinate>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

class DroneStatus
{
public:
    DroneStatus();

    //! Creates a droneStatus object from a Json status messages that can be received from the drone.
    static DroneStatus fromJsonString(QString string);

    /*****************
    * Getters/Setters
    *****************/
    double getOrientation() const;
    void setOrientation(double value);

    QGeoCoordinate getPosition() const;
    void setPosition(const QGeoCoordinate &value);

    double getGimballAngle() const;
    void setGimballAngle(double value);

    double getSpeed() const;
    void setSpeed(double value);

    double getBatteryLevel() const;
    void setBatteryLevel(double value);

    int getDroneState() const;
    void setDroneState(int value);

    QTime getTimestampDrone() const;
    void setTimestampDrone(const QTime &value);

    QTime getTimestampWorkstation() const;
    void setTimestampWorkstation(const QTime &value);

private:
    /**************
    * Attributes
    **************/
    //! contains long, lat and alt
    QGeoCoordinate position;
    //! orientation (0-360 degrees)
    double orientation;
    double gimballAngle;
    double speed;
    double batteryLevel;
    int droneState;
    QTime timestampDrone;
    QTime timestampWorkstation;

};

#endif // DRONESTATUS_H
