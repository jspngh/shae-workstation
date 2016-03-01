#ifndef SIMPLEPATHALGORITHM_H
#define SIMPLEPATHALGORITHM_H
#include <list>
#include "pathalgorithm.h"
#include <QGeoRectangle>

//! A simple path algoritm that extends PathAlgorithm
class SimplePathAlgorithm : public PathAlgorithm
{
public:
    SimplePathAlgorithm();
    SimplePathAlgorithm(QGeoCoordinate start);
    ~SimplePathAlgorithm();

    //! implements the specified method from the abstract PathAlgorithm class in a simple approach.
    std::list<QGeoCoordinate> calculateWaypoints(QGeoRectangle area, double visionWidth);
    void setWaypointsForDrones(QGeoRectangle area, std::list<Drone>* drones);

};

#endif // SIMPLEPATHALGORITHM_H
