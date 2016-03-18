#include "dronestatus.h"

#include <QtDebug>


DroneStatus::DroneStatus()
{

}

DroneStatus DroneStatus::fromJsonString(QString string)
{
    //create status object to return and set current time
    DroneStatus status = DroneStatus();
    status.setTimestampRecievedWorkstation(QTime::currentTime());

    //Start parsing the string
    QJsonDocument jsondoc = QJsonDocument::fromJson(string.toUtf8());

    //not a Json message
    if(!jsondoc.isObject()){
        throw ParseException("Not a Json object", string);
    }
    QJsonObject json = jsondoc.object();
    QString messageType = json["MessageType"].toString();

    //not a status message
    if(messageType != "status"){
         throw ParseException("Not a status message", string);
    }
    QJsonValue value = json["Orientation"];
    if(! value.isUndefined()){
        status.setOrientation(value.toDouble());
    }
    value = json["Camera_angle"];
    if(! value.isUndefined()){
        status.setCameraAngle(value.toDouble());
    }
    value = json["Speed"];
    if(! value.isUndefined()){
        status.setSpeed(value.toDouble());
    }
    value= json["Selected_speed"];
    if(! value.isUndefined()){
        status.setSelectedSpeed(value.toDouble());
    }
    value = json["Battery_level"];
    if(! value.isUndefined()){
        status.setBatteryLevel(value.toDouble());
    }
    value= json["Drone_state"];
    if(! value.isUndefined()){
        status.setOrientation(value.toDouble());
    }












    return status;

}


/*****************
* Getters/Setters
*****************/

double DroneStatus::getOrientation() const
{
    return orientation;
}

void DroneStatus::setOrientation(double value)
{
    orientation = value;
}

double DroneStatus::getCameraAngle() const
{
    return cameraAngle;
}

void DroneStatus::setCameraAngle(double value)
{
    cameraAngle = value;
}

double DroneStatus::getSpeed() const
{
    return speed;
}

void DroneStatus::setSpeed(double value)
{
    speed = value;
}

double DroneStatus::getBatteryLevel() const
{
    return batteryLevel;
}

void DroneStatus::setBatteryLevel(double value)
{
    batteryLevel = value;
}

int DroneStatus::getDroneState() const
{
    return droneState;
}

void DroneStatus::setDroneState(int value)
{
    droneState = value;
}

QTime DroneStatus::getTimestampDrone() const
{
    return timestampDrone;
}

void DroneStatus::setTimestampDrone(const QTime &value)
{
    timestampDrone = value;
}

QTime DroneStatus::getTimestampRecievedWorkstation() const
{
    return timestampReceivedWorkstation;
}

void DroneStatus::setTimestampRecievedWorkstation(const QTime &value)
{
    timestampReceivedWorkstation = value;
}

double DroneStatus::getSelectedSpeed() const
{
    return selectedSpeed;
}

void DroneStatus::setSelectedSpeed(double value)
{
    selectedSpeed = value;
}

double DroneStatus::getHeight() const
{
    return height;
}

void DroneStatus::setHeight(double value)
{
    height = value;
}

double DroneStatus::getSelectedHeight() const
{
    return selectedHeight;
}

void DroneStatus::setSelectedHeight(double value)
{
    selectedHeight = value;
}

bool DroneStatus::getHeartbeat() const
{
    return heartbeat;
}

void DroneStatus::setHeartbeat(bool value)
{
    heartbeat = value;
}

QString DroneStatus::getManufacturer() const
{
    return manufacturer;
}

void DroneStatus::setManufacturer(const QString &value)
{
    manufacturer = value;
}

QString DroneStatus::getType() const
{
    return type;
}

void DroneStatus::setType(const QString &value)
{
    type = value;
}

QGeoCoordinate DroneStatus::getCurrentLocation() const
{
    return currentLocation;
}

void DroneStatus::setCurrentLocation(const QGeoCoordinate &value)
{
    currentLocation = value;
}

QGeoCoordinate DroneStatus::getNextWaypoint() const
{
    return nextWaypoint;
}

void DroneStatus::setNextWaypoint(const QGeoCoordinate &value)
{
    nextWaypoint = value;
}

QGeoCoordinate DroneStatus::getPreviousWaypoint() const
{
    return previousWaypoint;
}

void DroneStatus::setPreviousWaypoint(const QGeoCoordinate &value)
{
    previousWaypoint = value;
}

QList<QGeoCoordinate> DroneStatus::getNextWaypoints() const
{
    return nextWaypoints;
}

void DroneStatus::setNextWaypoints(const QList<QGeoCoordinate> &value)
{
    nextWaypoints = value;
}




