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





double Search::getGimbalAngle() const
{
    return gimbalAngle;
}

void Search::setGimbalAngle(double value)
{
    gimbalAngle = value;
}

double Search::getHeight() const
{
    return height;
}

void Search::setHeight(double value)
{
    height = value;
}
