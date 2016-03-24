#include "polygonpathalgorithm.h"

PolygonPathAlgorithm::PolygonPathAlgorithm()
    :PathAlgorithm()
{

}

PolygonPathAlgorithm::PolygonPathAlgorithm(QGeoCoordinate start)
    :PathAlgorithm(start)
{

}

PolygonPathAlgorithm::~PolygonPathAlgorithm()
{

}

QList<QGeoCoordinate>* PolygonPathAlgorithm::calculateWaypoints(QGeoRectangle area, double visionWidth)
{
    //TODO
    QList<QGeoCoordinate>* list = new QList<QGeoCoordinate>();
    return list;
}

void PolygonPathAlgorithm::setWaypointsForDrones(QGeoRectangle area, QList<Drone *> *drones)
{
    //TODO
}
