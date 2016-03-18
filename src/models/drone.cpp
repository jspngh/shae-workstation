#include "drone.h"

Drone::Drone()
{
    visionWidth = 1.0;
}

Drone::Drone(double visionWidth)
{
    if (visionWidth > MIN_VISIONWIDTH)
        this->visionWidth = visionWidth;
    else
        this ->visionWidth = MIN_VISIONWIDTH;
}

Drone::~Drone()
{
}

double Drone::getVisionWidth() const
{
    return this->visionWidth;
}

QList<QGeoCoordinate> Drone::getWaypoints()
{
    return this->waypoints;
}

void Drone::addWaypoint(const QGeoCoordinate &waypoint)
{
    this->waypoints.append(waypoint);
}

void Drone::addWaypoints(const QList<QGeoCoordinate> &waypoints)
{
    this->waypoints.append(waypoints);
}

