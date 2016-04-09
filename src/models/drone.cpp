#include "drone.h"

Drone::Drone()
    : Drone(6331, 5502, "10.1.1.10", "10.1.1.1", "sololink.sdp", MIN_VISIONWIDTH)

{

}

Drone::Drone(int dronePort, int streamPort, QString droneIp, QString controllerIp, QString streamPath, double visionWidth):
    guid(QUuid::createUuid()),
    dronePort(dronePort),
    streamPort(streamPort),
    controllerIp(controllerIp),
    droneIp(droneIp),
    streamPath(streamPath),
    visionWidth(visionWidth)
{
}

Drone::Drone(QUuid droneID, int dronePort, int streamPort, QString droneIp, QString controllerIp, QString streamPath, double visionWidth):
    guid(droneID),
    dronePort(dronePort),
    streamPort(streamPort),
    droneIp(droneIp),
    controllerIp(controllerIp),
    streamPath(streamPath),
    visionWidth(visionWidth)
{
}

Drone::~Drone()
{
}

/***********************
Getters/Setters
************************/

QUuid Drone::getGuid() const
{
    return this->guid;
}

int Drone::getDronePort()
{
    return this->dronePort;
}

int Drone::getStreamPort()
{
    return this->streamPort;
}

QString Drone::getDroneIp()
{
    return this->droneIp;
}

QString Drone::getControllerIp()
{
    return this->controllerIp;
}

double Drone::getVisionWidth() const
{
    return this->visionWidth;
}

void Drone::setVisionWidth(double visionWidth)
{
    this->visionWidth = visionWidth;
}

QString Drone::getStreamPath() const
{
    return streamPath;
}

void Drone::setStreamPath(const QString &value)
{
    streamPath = value;
}
