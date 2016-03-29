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

QList<DroneModule *> *Search::getDroneList() const
{
    return droneList;
}

void Search::setDroneList(QList<DroneModule *> *value)
{
    droneList = value;
}




