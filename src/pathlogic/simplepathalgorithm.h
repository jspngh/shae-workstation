#ifndef SIMPLEPATHALGORITHM_H
#define SIMPLEPATHALGORITHM_H

#include "pathalgorithm.h"
#include <QGeoRectangle>

/*! \brief A simple path algoritm that extends PathAlgorithm.
 * \ingroup Pathlogic
 * This path algorithm is very useful to calculate the path for a QGeoRectangle.
 * */

class SimplePathAlgorithm : public PathAlgorithm
{
public:

    //! The default constructor that sets the start Coordinate from the superclass equal to (0,0)
    SimplePathAlgorithm();
    /*! \brief Constructor that sets the start Coordinate from the superclass equal to the parameter.
     * \param start is the QGeoCoordinate of the place where we should start calculating, useful to go to the closest corner of the area first.
    */
    SimplePathAlgorithm(QGeoCoordinate start);
    //! The default destructor.
    ~SimplePathAlgorithm();

    /*! \brief calculateWaypoints function calculates the waypoints for a drone to cover an area.
     * This is done in a very simple way, just going north and south while incrementally
     * going west or east, starting from the closest corner of the defined area.
     * This method implements the pure virtual method from the super class.
     * \param area is a QGeoRectangle that represents the area for which we calculate waypoints.
     * \param visionWidth is used to define how wide the vision is of the drone, necessary to calculate the path.
     * \return A pointer to a list of QGeoCoordinates that contain the calculated waypoints
     */
    QList<QGeoCoordinate> *calculateWaypoints(QGeoRectangle area, double visionWidth);

    /*!
     * \brief calculateWaypoints for a polygonial area.
     * This method will just use the SimplePathAlgorithm for the *bounding* QGeoRectangle.
     * Thus the drone will go out of bounds when this method is used on a polygon. Use the polygonAlgorithm for the real calculation for a polygon.
     * \param area is a GeoPolygon that represents the area for which we calculate waypoints.
     * \param visionWidth is used to define how wide the vision is of the drone, necessary to calculate the path.
     * \return A pointer to a list of QGeoCoordinates that contain the calculated waypoints
     */
    QList<QGeoCoordinate> *calculateWaypoints(GeoPolygon area, double visionWidth);

    /*! \brief setWaypointsForDrones function sets the waypoints of each drone in the list of drones, based on the area provided to the function.
     * This function splits the area in smaller areas so that each drone has its own area. Then it calculates the waypoints for each drone,
     * based on their area, using the \ref calculateWaypoints() method.
     * \param area is the QGeoRectangle to be searched.
     * \param drones is a list of DroneModule pointers that together have to search the area.
    */
    void setWaypointsForDrones(QGeoRectangle area, QList<DroneModule *> drones);

    /*! \brief setWaypointsForDrones function sets the waypoints of each drone in the list of drones, based on the area provided to the function.
     * This function splits the area in smaller areas so that each drone has its own area. Then it calculates the waypoints for each drone,
     * based on their area, using the \ref calculateWaypoints() method.
     * Thus this method also uses the bounding rectangle for the GeoPolygon area. Use with caution!
     * \param area is the GeoPolygon to be searched.
     * \param drones is a list of DroneModule pointers that together have to search the area.
    */
    void setWaypointsForDrones(GeoPolygon area, QList<DroneModule *> drones);
};

#endif // SIMPLEPATHALGORITHM_H
