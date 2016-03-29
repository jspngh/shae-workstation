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
    QList<QGeoCoordinate> coordinates = QList<QGeoCoordinate>();
    coordinates.push_back(area.bottomLeft());
    coordinates.push_back(area.bottomRight());
    coordinates.push_back(area.topLeft());
    coordinates.push_back(area.topRight());

    return calculateWaypoints(GeoPolygon(coordinates),visionWidth);
}

QList<QGeoCoordinate>* PolygonPathAlgorithm::calculateWaypoints(GeoPolygon area, double visionWidth)
{
    //TODO

}

void PolygonPathAlgorithm::setWaypointsForDrones(QGeoRectangle area, QList<Drone *> *drones)
{
    QList<QGeoCoordinate> coordinates = QList<QGeoCoordinate>();
    coordinates.push_back(area.bottomLeft());
    coordinates.push_back(area.bottomRight());
    coordinates.push_back(area.topLeft());
    coordinates.push_back(area.topRight());
    setWaypointsForDrones(GeoPolygon(coordinates),drones);
}

void PolygonPathAlgorithm::setWaypointsForDrones(GeoPolygon area, QList<Drone *> *drones)
{
    //TODO

}
