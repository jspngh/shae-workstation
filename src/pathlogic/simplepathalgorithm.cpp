#include "simplepathalgorithm.h"
#include <QDebug>

SimplePathAlgorithm::SimplePathAlgorithm()
    : SimplePathAlgorithm(QGeoCoordinate(0.0, 0.0))
{

}

SimplePathAlgorithm::SimplePathAlgorithm(QGeoCoordinate start):
    PathAlgorithm(start)
{

}

SimplePathAlgorithm::~SimplePathAlgorithm()
{
}

QList<QGeoCoordinate> *SimplePathAlgorithm::calculateWaypoints(QGeoRectangle area, double visionWidth)
{
    //create empty list of Coordinates that will contain the waypoints
    QList<QGeoCoordinate> *list = new QList<QGeoCoordinate>();

    //calculate distances from the start coordinate to each corner of the rectangular area
    double d1 = start.distanceTo(area.topRight());
    double d2 = start.distanceTo(area.topLeft());
    double d3 = start.distanceTo(area.bottomRight());
    double d4 = start.distanceTo(area.bottomLeft());

    //Set closest corner as first waypoint.
    double min = std::min(std::min(d1, d2), std::min(d3, d4));
    if (min == d1)
        list->push_back(area.topRight());
    else if (min == d2)
        list->push_back(area.topLeft());
    else if (min == d3)
        list->push_back(area.bottomRight());
    else
        list->push_back(area.bottomLeft());

    //go up until most north coordinate reached if started south
    if (list->back().latitude() == area.bottomRight().latitude())
        list->push_back(QGeoCoordinate(area.topRight().latitude(), list->back().longitude()));
    else
        //go south because started north
        list->push_back(QGeoCoordinate(area.bottomRight().latitude(), list->back().longitude()));

    //then try to go 1 step(=visionWidth) in direction (=first west). If going west exceeds the most western coordinate of the rectangle, set direction to east and go 1 step east.
    Direction direction = WEST;
    if (PathAlgorithm::goDirection((list->back()), direction, visionWidth).longitude() < area.topLeft().longitude())
        direction = EAST;
    list->push_back(PathAlgorithm::goDirection((list->back()), direction, visionWidth));

    //Go all the way south, until most south coordinate reached. Go 1 step in direction again.
    //Go north again, and so forth, until all area is covered.

    while (list->back().longitude() < area.topRight().longitude() && list->back().longitude() > area.topLeft().longitude()) {
        //go south or north depending on location
        if (list->back().latitude() == area.topRight().latitude())
            list->push_back(QGeoCoordinate(area.bottomRight().latitude(), list->back().longitude()));
        else
            list->push_back(QGeoCoordinate(area.topRight().latitude(), list->back().longitude()));
        //go direction
        list->push_back(PathAlgorithm::goDirection((list->back()), direction, visionWidth));
    }

    //Go south or north for the last time
    if (list->back().latitude() == area.topRight().latitude())
        //Go south
        list->push_back(QGeoCoordinate(area.bottomRight().latitude(), list->back().longitude()));
    else
        //Go north
        list->push_back(QGeoCoordinate(area.topRight().latitude(), list->back().longitude()));


    //return list
    return list;
}

QList<QGeoCoordinate>* SimplePathAlgorithm::calculateWaypoints(GeoPolygon area, double visionWidth)
{
    return calculateWaypoints(area.getBoundingQGeoRectangle(), visionWidth);
}


void SimplePathAlgorithm::setWaypointsForDrones(QGeoRectangle area, QList<DroneModule *> *drones)
{
    int numDrones = drones->size();

    for (int i = 0; i < numDrones; i++) {
        QGeoCoordinate topleft = QGeoCoordinate(area.topLeft().latitude() , area.topLeft().longitude() + i * (area.width() / numDrones));
        QGeoCoordinate bottomright = QGeoCoordinate(area.bottomLeft().latitude() , area.bottomLeft().longitude() + (i + 1) * (area.width() / numDrones));
        QGeoRectangle areaPerDrone = QGeoRectangle(topleft, bottomright);
        double visionPerDrone = (*drones)[i]->getVisionWidth();
        (*drones)[i]->setWaypoints(calculateWaypoints(areaPerDrone, visionPerDrone));
    }
}

void SimplePathAlgorithm::setWaypointsForDrones(GeoPolygon area, QList<Drone *> *drones)
{
    setWaypointsForDrones(area.getBoundingQGeoRectangle(), drones);
}

