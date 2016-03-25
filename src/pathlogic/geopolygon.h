#ifndef GEOPOLYGON_H
#define GEOPOLYGON_H
#include <QGeoShape>
#include <QGeoRectangle>

/*!
 * \brief The GeoPolygon class describes a convex polygon area.
 * It is derived from QGeoShape, the base class of QGeoRectangle.
 */
class GeoPolygon : public QGeoShape
{
public:
    GeoPolygon();
    GeoPolygon(QList<QGeoCoordinate> coordinates);

    QGeoRectangle getBoundingQGeoRectangle();

    /*! \brief This functions calculates the z-component of the cross product to know if the points
        make a clock-wise turn or not, useful for checking if a hull is valid.
        \return returns positive if OAB makes a counter-clockwise turn,
        negative if clockwise and zero if points are collinear. */
    double crossProduct(QGeoCoordinate O, QGeoCoordinate A, QGeoCoordinate B);
    /***********
     * Getters *
     ***********/
    QList<QGeoCoordinate> getCoordinates() const;

    QList<QGeoCoordinate> getUpperHull() const;

    QList<QGeoCoordinate> getLowerHull() const;

    QGeoCoordinate getMostWestCoordinate() const;

    QGeoCoordinate getMostEastCoordinate() const;

private:

    //! Checks if the list of coordinates forms a valid convex polygon.
    bool isValid() const;

    //! The list of coordinates contained by the polygon.
    QList<QGeoCoordinate> coordinates;

    //The following attributes are only for internal caching use, these should never be set.
    //! contains all coordinates from the upper hull.
    QList<QGeoCoordinate> upperHull;
    //! contains all coordinates from the lower hull.
    QList<QGeoCoordinate> lowerHull;
    QGeoCoordinate mostWestCoordinate;
    QGeoCoordinate mostEastCoordinate;
};

#endif // GEOPOLYGON_H
