#ifndef POLYGONPATHALGORITHM_H
#define POLYGONPATHALGORITHM_H
#include "pathalgorithm.h"
#include <QGeoRectangle>


class PolygonPathAlgorithm : public PathAlgorithm
{
public:
    PolygonPathAlgorithm();

    PolygonPathAlgorithm(QGeoCoordinate start);

    ~PolygonPathAlgorithm();
    /*!
     * \brief calculateWaypoints calculates waypointcoordinates to cover a certain area, when given a certain visionwidth.
     * \param area contains two QGeoCoordinate objects. The first QGeoCoordinate contains the coordinates of the top left point
     * and the second coordinate contains the bottom right point. The Order is important!
     * \param visionWidth width in degrees the drone's camera sees
     * \return a pointer to a list of coordinates. The coordinates are the waypoints for the drone.
     * This function will just use the calculateWaypoints(QGeoShape area, double visionWidth) function of this class.
     */
    QList<QGeoCoordinate> *calculateWaypoints(QGeoRectangle area, double visionWidth);

    //! Same but for a GeoPolygon area, more advanced.
    QList<QGeoCoordinate> *calculateWaypoints(GeoPolygon area, double visionWidth);

    void setWaypointsForDrones(QGeoRectangle area, QList<Drone *> *drones);

    //! Same but for a GeoPolygon area.
    void setWaypointsForDrones(GeoPolygon area, QList<Drone *> *drones);

};

#endif // POLYGONPATHALGORITHM_H
