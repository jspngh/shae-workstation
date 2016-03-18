#include "pathalgorithm.h"

PathAlgorithm::PathAlgorithm()
{
    this->start = QGeoCoordinate(0.0, 0.0);
}

PathAlgorithm::PathAlgorithm(QGeoCoordinate start)
{
    this->start = start;
}

PathAlgorithm::~PathAlgorithm()
{

}

QGeoCoordinate PathAlgorithm::goDirection(QGeoCoordinate start, Direction direction, double distance)
{
    switch (direction) {
    case NORTH:
        return   QGeoCoordinate(start.latitude() + distance, start.longitude());
        break;
    case SOUTH:
        return   QGeoCoordinate(start.latitude() - distance, start.longitude());
        break;
    case WEST:
        return   QGeoCoordinate(start.latitude(), start.longitude() - distance);
        break;
    case EAST:
        return   QGeoCoordinate(start.latitude(), start.longitude() + distance);
        break;
    default:
        return start ;
        break;
    }

}

