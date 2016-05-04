#ifndef PATHALGORITHM_H
#define PATHALGORITHM_H

#include <GeoPolygon.h>
#include <QGeoCoordinate>
#include <QGeoRectangle>
#include <QObject>
#include "communication/dronemodule.h"
#include "core/mediator.h"
#include "models/drone.h"
#include "models/search.h"

enum Direction {
    EAST = 1, WEST = -1
};

/*! PathAlgorithm is an abstract class which can be extended by implementations of an algorithm.
 * \ingroup Pathlogic
 * */
class PathAlgorithm: public QObject
{
    Q_OBJECT

public:
    QGeoCoordinate start; //!< We will need this to efficiently divide search areas over the available drones, and to plan the beginning of the path as close to the start as possible.

    PathAlgorithm(QObject *p = 0);
    PathAlgorithm(QGeoCoordinate start, QObject *p = 0);
    PathAlgorithm(const PathAlgorithm &algo);
    ~PathAlgorithm();

    /*!
     * \brief calculateWaypoints calculates waypointcoordinates to cover a certain area, when given a certain visionwidth.
     * \param area contains two QGeoCoordinate objects. The first QGeoCoordinate contains the coordinates of the top left point
     * and the second coordinate contains the bottom right point. The Order is important!
     * \param visionWidth width in degrees the drone's camera sees
     * \return a pointer to a list of coordinates. The coordinates are the waypoints for the drone.
     */
    virtual QList<QGeoCoordinate> *calculateWaypoints(QGeoRectangle area, double visionWidth) = 0;

    //!The function to calculate waypoints in a polygonial area.
    virtual QList<QGeoCoordinate> *calculateWaypoints(GeoPolygon area, double visionWidth) = 0;

    /*!
    * \brief setWaypointsForDrones divides a rectangular area in multiple rectangles and saves the resulting waypoints in each drone object.
    * \param area contains two QGeoCoordinate objects. The first QGeoCoordinate contains the coordinates of the top left point
    * and the second coordinate contains the bottom right point. The Order is important!
    * \param drones every drone in the list will be assigned an area
    */
    virtual void setWaypointsForDrones(QGeoRectangle area, QList<DroneModule *> drones) = 0;

    //! The function to set the waypoints for all drones for a polygonial area.
    virtual void setWaypointsForDrones(GeoPolygon area, QList<DroneModule *> drones) = 0;

    // Setter
    void setMediator(Mediator *mediator);

    //! returns a new coordinate based on a certain distance and direction from a previous coordinate.
    static QGeoCoordinate goDirection(QGeoCoordinate start, Direction direction, double distance);

    /*!
     * \brief goDirectionBetween
     * \param start is the starting location
     * \param coordinate1 determines direction together with coordinate2
     * \param coordinate2 determines direction together with coordinate1
     * \param distance is the distance in decimal degrees, alongside the equator.
     * \param direction is East or West
     * \return a coordinate that is a distance of start, in the direction of the line between coordinate1 and coordinate2
     */
    static QGeoCoordinate goDirectionBetween(QGeoCoordinate start, QGeoCoordinate coordinate1, QGeoCoordinate coordinate2, double distance, Direction direction);

public slots:
    void startSearch(Search *s);

signals:
    void pathCalculated(Search *s);

private:
    Mediator *mediator;
};

#endif // PATHALGORITHM_H
