#ifndef DRONE_H
#define DRONE_H
#include <QGeoCoordinate>

/*! \brief This should become the class that represents a drone on the workstation

*/
class Drone
{
private:
    const double MIN_VISIONWIDTH = 0.00000000001; //!< This is a lower bound to the visionwidth, since visionWidth cannot be zero.

    double visionWidth; //!< This attribute tells how wide the vision of the drone is. This is useful to calculate the waypoints. It should use the same scale as the coordinates used in the waypointplanning algorithms.
    QList<QGeoCoordinate> waypoints;

public:
    Drone();
    Drone(double visionWidth);
    ~Drone();

    double getVisionWidth() const;
    QList<QGeoCoordinate> getWaypoints();
    void addWaypoint(const QGeoCoordinate &waypoint);
    void addWaypoints(const QList<QGeoCoordinate> &waypoints);
};

#endif // DRONE_H
