#include "search.h"


Search::Search()
    : searchID(QUuid::createUuid())
{
    // TODO set time
}

Search::~Search()
{
    delete droneList;
}

QTime Search::getStartTime() const
{
    return startTime;
}

QGeoRectangle Search::getArea() const
{
    return area;
}

void Search::setArea(const QGeoRectangle &value)
{
    area = value;
}

QList<Drone *> *Search::getDroneList() const
{
    return droneList;
}

void Search::setDroneList(QList<Drone *> *value)
{
    droneList = value;
}





int Search::getGimbalAngle() const
{
    return gimbalAngle;
}

void Search::setGimbalAngle(int value)
{
    gimbalAngle = value;
}

int Search::getHeight() const
{
    return height;
}

void Search::setHeight(int value)
{
    height = value;
}
