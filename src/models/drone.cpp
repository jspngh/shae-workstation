#include "drone.h"


Drone::Drone()
    : Drone(6331, "10.1.1.10", MIN_VISIONWIDTH)
{

}

Drone::Drone(int portNr, QString serverIp, double visionWidth):
    guid(QUuid::createUuid()),
    portNr(portNr),
    serverIp(serverIp),
    visionWidth(visionWidth)
{

}

Drone::Drone(const Drone &d)
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
    return this->portNr;
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

