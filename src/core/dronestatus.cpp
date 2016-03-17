#include "dronestatus.h"

#include <QtDebug>


DroneStatus::DroneStatus()
{

}

DroneStatus DroneStatus::fromJsonString(QString string)
{
   QJsonDocument jsondoc = QJsonDocument::fromJson(string.toUtf8());
   QJsonObject json = jsondoc.object();
   QString messageType = json["MessageType"].toString();
   if(messageType != "status"){
       qDebug() << "The received message:" + string + ", is not a status message.";
       return DroneStatus();
   }




   DroneStatus status = DroneStatus();
   return status;

}

double DroneStatus::getOrientation() const
{
    return orientation;
}

void DroneStatus::setOrientation(double value)
{
    orientation = value;
}

QGeoCoordinate DroneStatus::getPosition() const
{
    return position;
}

void DroneStatus::setPosition(const QGeoCoordinate &value)
{
    position = value;
}

double DroneStatus::getGimballAngle() const
{
    return gimballAngle;
}

void DroneStatus::setGimballAngle(double value)
{
    gimballAngle = value;
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

QTime DroneStatus::getTimestampWorkstation() const
{
    return timestampWorkstation;
}

void DroneStatus::setTimestampWorkstation(const QTime &value)
{
    timestampWorkstation = value;
}
