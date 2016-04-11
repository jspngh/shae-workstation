#include "drone.h"

Drone::Drone()
{
    guid = QUuid::createUuid();
    dronePort = 6331;
    streamPort = 5502;
    controllerIp = "10.1.1.10";
    droneIp = "10.1.1.1";
    streamPath = "sololink.sdp";
    visionWidth =MIN_VISIONWIDTH;
}

Drone::Drone(const Drone &d){
    guid = d.guid;
    dronePort = d.dronePort;
    streamPort = d.streamPort;
    controllerIp = d.controllerIp;
    droneIp = d.droneIp;
    streamPath= d.streamPath;
    visionWidth = d.visionWidth;
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
