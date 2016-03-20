#ifndef PATHALGORITHM_H
#define PATHALGORITHM_H

#include <QGeoCoordinate>
#include <QGeoRectangle>
#include "models/drone.h"


enum Direction {
    NORTH, SOUTH, EAST, WEST
};

//! PathAlgorithm is an abstract class which can be extended by implementations of an algorithm.
class PathAlgorithm
{

public:

    QGeoCoordinate start; //!< We will need this to efficiently divide search areas over the available drones, and to plan the beginning of the path as close to the start as possible.

    PathAlgorithm();
    PathAlgorithm(QGeoCoordinate start);
    ~PathAlgorithm();

    //! calculates waypointcoordinates to cover a certain area, when given a certain visionwidth.
    virtual QList<QGeoCoordinate> calculateWaypoints(QGeoRectangle area, double visionWidth) = 0;

    //! divides a rectangular area in multiple rectangles and saves the resulting waypoints in each drone object.

    virtual void setWaypointsForDrones(QGeoRectangle area, QList<Drone *> *drones) = 0;


protected:
    //! returns a new coordinate based on a certain distance and direction from a previous coordinate.
    static QGeoCoordinate goDirection(QGeoCoordinate start, Direction direction, double distance);

};




#endif // PATHALGORITHM_H
