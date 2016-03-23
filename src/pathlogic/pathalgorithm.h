#ifndef PATHALGORITHM_H
#define PATHALGORITHM_H

#include <QObject>

#include <QGeoCoordinate>
#include <QGeoRectangle>

#include "models/drone.h"
#include "models/search.h"

class Controller;


enum Direction {
    NORTH, SOUTH, EAST, WEST
};

//! PathAlgorithm is an abstract class which can be extended by implementations of an algorithm.
class PathAlgorithm: public QObject
{
    Q_OBJECT

public:

    QGeoCoordinate start; //!< We will need this to efficiently divide search areas over the available drones, and to plan the beginning of the path as close to the start as possible.

    PathAlgorithm(QObject *p = 0);
    PathAlgorithm(QGeoCoordinate start, QObject *p = 0);
    ~PathAlgorithm();

    /*!
     * \brief calculateWaypoints calculates waypointcoordinates to cover a certain area, when given a certain visionwidth.
     * \param area contains two QGeoCoordinate objects. The first QGeoCoordinate contains the coordinates of the top left point
     * and the second coordinate contains the bottom right point. The Order is important!
     * \param visionWidth width in degrees the drone's camera sees
     * \return a pointer to a list of coordinates. The coordinates are the waypoints for the drone.
     */
    virtual QList<QGeoCoordinate> *calculateWaypoints(QGeoRectangle area, double visionWidth) = 0;

    /*!
    * \brief setWaypointsForDrones divides a rectangular area in multiple rectangles and saves the resulting waypoints in each drone object.
    * \param area contains two QGeoCoordinate objects. The first QGeoCoordinate contains the coordinates of the top left point
    * and the second coordinate contains the bottom right point. The Order is important!
    * \param drones every drone in the list will be assigned an area
    */
    virtual void setWaypointsForDrones(QGeoRectangle area, QList<Drone*> *drones) = 0;

    // Setter

    void setController(Controller *value);

protected:
    //! returns a new coordinate based on a certain distance and direction from a previous coordinate.
    static QGeoCoordinate goDirection(QGeoCoordinate start, Direction direction, double distance);

private slots:
    void onStartSearch(Search *s);

signals:
    void pathCalculated(Search *s);



private:
    Controller *controller;

};




#endif // PATHALGORITHM_H
