#include "drone.h"


Drone::Drone()
    : Drone(6331, 5502, "10.1.1.10", "sololink.sdp", MIN_VISIONWIDTH)
{

}

Drone::Drone(int dataPort, int streamPort, QString serverIp, QString streamPath, double visionWidth):
    guid(QUuid::createUuid()),
    dataPort(dataPort),
    streamPort(streamPort),
    serverIp(serverIp),
    streamPath(streamPath),
    visionWidth(visionWidth)
{

}

Drone::Drone(QUuid droneID, int dataPort, int streamPort, QString serverIp, QString streamPath, double visionWidth):
    guid(droneID),
    dataPort(dataPort),
    streamPort(streamPort),
    serverIp(serverIp),
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

int Drone::getPortNr()
{
    return this->dataPort;
}

int Drone::getStreamPortNr()
{
    return this->streamPort;
}

QString Drone::getServerIp()
{
    return this->serverIp;
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

