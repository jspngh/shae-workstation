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
    /*!
     * \brief GeoPolygon default constructor
     * Creates a simple test polygon around (0.0,0.0)
     * Should not be used for serious purposes.
     */
    GeoPolygon();
    /*!
     * \brief GeoPolygon constructor that should be used
     * \param coordinates, a list containing coordinates that should be inside the polygon.
     * The constructor will create a convex polygon that will contain all coordinates
     * in its area, but not necessarily contains all the coordinates on its border (saved in the coordinates attribute.
     */
    GeoPolygon(QList<QGeoCoordinate> coordinates);

    /*!
     * \brief fromHull returns the field coordinates if upperhull and lowerhull are already calculated.
     * \param upper is a list of coordinates describing the upperHull.
     * \param lower is a list of coordinates describing the lowerHull.
     * \return A list of coordinates, usefull for setting the coordinates field after calculating
     *  upperHull and lowerHull in the constructor.
     */
    static QList<QGeoCoordinate> fromHull(QList<QGeoCoordinate> upper, QList<QGeoCoordinate> lower);

    //! Constructs a new QGeoRectangle, of minimum size, containing all of the coordinates.
    QGeoRectangle getBoundingQGeoRectangle();

    /*! \brief This functions calculates the z-component of the cross product to know if the points
        make a clock-wise turn or not, useful for checking if a hull is valid.
        \return returns positive if OAB makes a counter-clockwise turn,
        negative if clockwise and zero if points are collinear. */
    static double crossProduct(QGeoCoordinate O, QGeoCoordinate A, QGeoCoordinate B);

    //! Compares two coordinates, used to sort a list of coordinates in the constructor of the GeoPolygon.
    static int compare(const QGeoCoordinate left, const QGeoCoordinate right);

    //! Compares two coordinates, but sort first according to latitude.
    static int compareLatitude(const QGeoCoordinate left, const QGeoCoordinate right);

    //! Checks if the saved coordinates forms a valid convex polygon.
    //! TODO: implement rest of checks.
    bool isValid() const;

    //! Makes a string of a polygon for debugging purposes.
    QString toString();

    /***********
     * Getters *
     ***********/
    /*!
     * \brief getCoordinates
     * \return List of all the coordinates from the polygon, sorted clockwise starting from the mostWestCoordinate.
     */
    QList<QGeoCoordinate> getCoordinates() const;

    /*!
     * \brief getUpperHull
     * \return List of coordinates in upper hull, including mostEastCoordinate and mostEastCoordinate, sorted from West to East.
     */
    QList<QGeoCoordinate> getUpperHull() const;

    /*!
     * \brief getLowerHull
     * \return List of coordinates in lower hull, including mostEastCoordinate and mostEastCoordinate, sorted from West to East.
     */
    QList<QGeoCoordinate> getLowerHull() const;

    QGeoCoordinate getMostWestCoordinate() const;

    QGeoCoordinate getMostEastCoordinate() const;

private:


    //! The list of coordinates contained by the polygon.
    QList<QGeoCoordinate> coordinates;

    //The following attributes are only for internal caching use, these should never be set.
    //! contains all coordinates from the upper hull, including mostWest and mostEast, sorted from West to East.
    QList<QGeoCoordinate> upperHull;
    //! contains all coordinates from the lower hull, including mostWest and mostEast, sorted from West to East.
    QList<QGeoCoordinate> lowerHull;
    QGeoCoordinate mostWestCoordinate;
    QGeoCoordinate mostEastCoordinate;
};

#endif // GEOPOLYGON_H
