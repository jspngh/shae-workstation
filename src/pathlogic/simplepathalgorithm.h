#ifndef SIMPLEPATHALGORITHM_H
#define SIMPLEPATHALGORITHM_H

#include "pathalgorithm.h"
#include <QGeoRectangle>

//! A simple path algoritm that extends PathAlgorithm
class SimplePathAlgorithm : public PathAlgorithm
{
public:

    //! The default constructor that sets the start Coordinate from the superclass equal to (0,0)
    SimplePathAlgorithm();
    //! Constructor that sets the start Coordinate from the superclass equal to the parameter.
    SimplePathAlgorithm(QGeoCoordinate start);
    //! The default destructor.
    ~SimplePathAlgorithm();

    /*! \brief calculateWaypoints function calculates the waypoints for a drone to cover an area.
     * This is done in a very simple way, just going north and south while incrementally
     * going west or east, starting from the closest corner of the defined area.
     * It uses visionWidth to define how wide the vision is of the drone, necessary to calculate the path.
     * This method implements the pure virtual method from the super class.
     */
    QList<QGeoCoordinate> *calculateWaypoints(QGeoRectangle area, double visionWidth);

    /*!
     * \brief calculateWaypoints for a polygonial area,
     * but this method will just use the SimplePathAlgorithm for the bounding rectangle.
     * Thus the drone will go out of bounds when this meethod is used on a polygon. Use the polygonAlgorithm for the real calculation for a polygon.
     */
    QList<QGeoCoordinate> *calculateWaypoints(GeoPolygon area, double visionWidth);



    /*! \brief setWaypointsForDrones function sets the waypoints of each drone in the list of drones, based on the area provided to the function.
     * This function splits the area in smaller areas so that each drone has its own area. Then it calculates the waypoints for each drone,
     * based on their area, using the \ref calculateWaypoints() method.
    */
    void setWaypointsForDrones(QGeoRectangle area, QList<DroneModule *> *drones);

    /*! \brief setWaypointsForDrones function sets the waypoints of each drone in the list of drones, based on the area provided to the function.
     * This function splits the area in smaller areas so that each drone has its own area. Then it calculates the waypoints for each drone,
     * based on their area, using the \ref calculateWaypoints() method.
     * Thus this method also uses the bounding rectangle for the GeoPolygon area. Use with caution!
    */
    void setWaypointsForDrones(GeoPolygon area, QList<DroneModule *> *drones);

};

#endif // SIMPLEPATHALGORITHM_H
