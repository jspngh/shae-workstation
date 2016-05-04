#ifndef POLYGONPATHALGORITHM_H
#define POLYGONPATHALGORITHM_H
#include "pathalgorithm.h"
#include <QGeoRectangle>
#include <QPair>

/*!
 * \brief The PolygonPathAlgorithm class can compute a path for drones inside a polygon.
 * Around edges it can be a little bit innacurate due to differentation of hulls.
 * \ingroup Pathlogic
 */
class PolygonPathAlgorithm : public PathAlgorithm
{
public:
    //! the default constructor
    PolygonPathAlgorithm();

    //! constructor that sets start
    //! \param start is the coordinate used to calculated if the most west point is the closest or the most east point.
    PolygonPathAlgorithm(QGeoCoordinate start);

    //! the copy constructor
    PolygonPathAlgorithm(const PolygonPathAlgorithm &);

    //!the default destructor
    ~PolygonPathAlgorithm();
    /*!
     * \brief calculateWaypoints calculates waypointcoordinates to cover a certain area, when given a certain visionwidth.
     * makes a polygon of the rectangle and uses the polygon method.Should not be used in real applications,
     *  since simplepathalgorithm is way better (more efficient + more accurate) for rectangular areas.
     * \param area is the QGeoRectangle that needs to be searched.
     * \param visionWidth is how wide the drone sees, in decimal degrees longitude.
     * \return a pointer to the list of calculated QGeoCoordinates.
     */
    QList<QGeoCoordinate> *calculateWaypoints(QGeoRectangle area, double visionWidth);

    /*!
     * \brief calculateWaypoints calculates waypointcoordinates to cover a certain area, when given a certain visionwidth.
     * The method to use for a GeoPolygon area. Warning: some coordinates may be a little bit out of the area, but no more than visionWidth.
     *  \param area is the GeoPolygon that needs to be searched.
     * \param visionWidth is how wide the drone sees, in decimal degrees longitude.
     * \return a pointer to the list of calculated QGeoCoordinates.
     */
    QList<QGeoCoordinate> *calculateWaypoints(GeoPolygon area, double visionWidth);

    /*!
     * \brief setWaypointsForDrones sets the waypoints attribute of each drone.
     * Converts the rectangle to a polygon and then uses that method. Should not be used in real applications,
     *  since simplepathalgorithm is way better (more efficient + more accurate) for rectangular areas.
     * \param area is the QGeoRectangle to be searched.
     * \param is the list of DroneMoudle pointers that will search the area together.
     */
    void setWaypointsForDrones(QGeoRectangle area, QList<DroneModule *> drones);

    /*!
     * \brief setWaypointsForDrones sets the waypoints attribute of each drone.
     * Calculates the waypoints for a GeoPolygon area.
     * \param area is the GeoPolygon to be searched.
     * \param is the list of DroneMoudle pointers that will search the area together.
     */
    void setWaypointsForDrones(GeoPolygon area, QList<DroneModule *> drones);

    //! \brief calculates a the neighbouring pair from the specified hull.
    //! \param from is the coordinate that will be used to get the West and East neighbours from the given hull
    //! \param hull is the list of coordinates to find the next coordinate in the west and the next coordinate in the east direction.
    //! \return A pair containing the coordinates east and west of "from" coordinate, inside the given hull.
    static QPair<QGeoCoordinate, QGeoCoordinate> getNeighbouringEdges(QGeoCoordinate from, QList<QGeoCoordinate> hull);


};

#endif // POLYGONPATHALGORITHM_H
