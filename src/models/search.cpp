#include "search.h"


Search::Search()
    : searchID(QUuid::createUuid())
{
    // TODO set time
}

Search::Search(QList<Drone> *droneList, QGeoRectangle area)
    : searchID(QUuid::createUuid()),
      droneList(droneList),
      area(area)
{
    // TODO set time
}

Search::~Search()
{
    delete droneList;
    delete waypoints;
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

QList<Drone> *Search::getDroneList() const
{
    return droneList;
}

void Search::setDroneList(QList<Drone> *value)
{
    droneList = value;
}

QList<QGeoCoordinate> *Search::getWaypoints() const
{
    return waypoints;
}

void Search::setWaypoints(QList<QGeoCoordinate> *value)
{
    waypoints = value;
}



