#ifndef POLYGONPATHALGORITHM_H
#define POLYGONPATHALGORITHM_H
#include "pathalgorithm.h"
#include <QGeoRectangle>
#include <QPair>


class PolygonPathAlgorithm : public PathAlgorithm
{
public:
    PolygonPathAlgorithm();

    PolygonPathAlgorithm(QGeoCoordinate start);

    PolygonPathAlgorithm(const PolygonPathAlgorithm&);

    ~PolygonPathAlgorithm();
    /*!
     * \brief calculateWaypoints calculates waypointcoordinates to cover a certain area, when given a certain visionwidth.
     * makes a polygon of the rectangle and uses the polygon method.
     */
    QList<QGeoCoordinate> *calculateWaypoints(QGeoRectangle area, double visionWidth);

    /*!
     * \brief calculateWaypoints calculates waypointcoordinates to cover a certain area, when given a certain visionwidth.
     * The method to use for a GeoPolygon area.
     */
    QList<QGeoCoordinate> *calculateWaypoints(GeoPolygon area, double visionWidth);

    /*!
     * \brief setWaypointsForDrones sets the waypoints attribute of each drone.
     * Converts the rectangle to a polygon and then uses that method.
     */
    void setWaypointsForDrones(QGeoRectangle area, QList<Drone *> *drones);

    //! Same but for a GeoPolygon area.
    void setWaypointsForDrones(GeoPolygon area, QList<Drone *> *drones);


protected:
    QPair<QGeoCoordinate,QGeoCoordinate> getNeighbouringEdges(QGeoCoordinate from, QList<QGeoCoordinate> hull);

};

#endif // POLYGONPATHALGORITHM_H
