#include "GeoPolygon.h"
#include <algorithm>
#include <QtDebug>

GeoPolygon::GeoPolygon()
    : QGeoShape()
{
    mostWestCoordinate = QGeoCoordinate(0.0, 0.0);
    mostEastCoordinate = QGeoCoordinate(0.0, 1.0);
    lowerHull = QList<QGeoCoordinate>();
    upperHull = QList<QGeoCoordinate>();
    lowerHull.push_back(mostWestCoordinate);
    lowerHull.push_back(mostEastCoordinate);
    upperHull.push_back(mostWestCoordinate);
    upperHull.push_back(QGeoCoordinate(1.0, 0.4));
    upperHull.push_back(QGeoCoordinate(1.0, 0.6));
    upperHull.push_back(mostEastCoordinate);
    coordinates = fromHull(upperHull, lowerHull);

    if (!isValid()) {
        qDebug() << "Something is wrong with the construction of this GeoPolygon";
    }
}

GeoPolygon::GeoPolygon(QList<QGeoCoordinate> coordinates)
    : QGeoShape()
{
    std::sort(coordinates.begin(), coordinates.end(), compare);
    mostWestCoordinate = coordinates.front();
    mostEastCoordinate = coordinates.back();

    //create upperhull and lowerhull
    int size = coordinates.size();
    lowerHull = QList<QGeoCoordinate>();
    for (int i = 0; i < size; ++i) {
        while (lowerHull.size() >= 2 &&
                crossProduct(lowerHull[lowerHull.size() - 2],
                             lowerHull[lowerHull.size() - 1],
                             coordinates[i]) <= 0.0) {
            lowerHull.pop_back();
        }
        lowerHull.push_back(coordinates[i]);

    }

    upperHull = QList<QGeoCoordinate>();
    for (int i = 0; i < size; ++i) {
        while (upperHull.size() >= 2 &&
                crossProduct(upperHull[upperHull.size() - 2],
                             upperHull[upperHull.size() - 1],
                             coordinates[i]) >= 0.0) {
            upperHull.pop_back();
        }
        upperHull.push_back(coordinates[i]);

    }
    this->coordinates = fromHull(upperHull, lowerHull);
    if (!isValid()) {
        qDebug() << "Something is wrong with the construction of this GeoPolygon";
    }

}

GeoPolygon::GeoPolygon(const GeoPolygon &other)
    : QGeoShape()
{
    this->coordinates = other.coordinates;
    this->upperHull = other.upperHull;
    this->lowerHull = other.lowerHull;
    this->mostWestCoordinate = other.mostWestCoordinate;
    this->mostEastCoordinate = other.mostEastCoordinate;
}

QList<QGeoCoordinate> GeoPolygon::fromHull(QList<QGeoCoordinate> upper, QList<QGeoCoordinate> lower)
{
    QList<QGeoCoordinate> list = QList<QGeoCoordinate>(upper);
    QList<QGeoCoordinate> lowerlist = QList<QGeoCoordinate>(lower);
    //pop the back and front, since upperhull already should contain these.
    lowerlist.pop_back();
    lowerlist.pop_front();
    //start from the end of the lowerhull, and add it to coordinates to create a list in clockwise order.
    while (!lowerlist.empty()) {
        list.append(lowerlist.back());
        lowerlist.pop_back();
    }
    return list;
}

int GeoPolygon::compare(const QGeoCoordinate left, const QGeoCoordinate right)
{
    if (left.longitude() == right.longitude())
        return left.latitude() < right.latitude();
    else return left.longitude() < right.longitude();
}

int GeoPolygon::compareLatitude(const QGeoCoordinate left, const QGeoCoordinate right)
{
    if (left.latitude() == right.latitude())
        return left.longitude() < right.longitude();
    else return left.latitude() < right.latitude();
}

double GeoPolygon::crossProduct(QGeoCoordinate O, QGeoCoordinate A, QGeoCoordinate B)
{
    return (A.longitude() - O.longitude())
           * (B.latitude() - O.latitude())
           - (A.latitude() - O.latitude())
           * (B.longitude() - O.longitude());
}

bool GeoPolygon::isValid() const
{
    //check if mostEast en mostWest are correct
    //qDebug() << "isvalid";

    foreach (QGeoCoordinate coordinate, coordinates) {
        if (coordinate.longitude() < mostWestCoordinate.longitude()) {
            qDebug() << "1";
            return false;
        }
        if (coordinate.longitude() > mostEastCoordinate.longitude()) {
            qDebug() << "2";
            return false;
        }
    }


    //mostleft and most right should be in both hulls at resp. front and back
    if (upperHull.front() != mostWestCoordinate) {
        qDebug() << "6";
        return false;
    }
    if (lowerHull.front() != mostWestCoordinate) {
        qDebug() << "7";
        return false;
    }
    if (upperHull.back() != mostEastCoordinate || lowerHull.back() != mostEastCoordinate) {
        qDebug() << "8";
        return false;
    }

    //check if upperhull curves clockwise
    for (int i = 2; i < upperHull.size(); i++) {
        if (crossProduct(upperHull[i - 2], upperHull[i - 1], upperHull[i]) > 0.0) {
            qDebug() << "3";
            return false;
        }
    }

    //check if lowerhull curves counter-clockwise
    for (int i = 2; i < lowerHull.size(); i++) {
        if (crossProduct(lowerHull[i - 2], lowerHull[i - 1], lowerHull[i]) < 0.0) {

            qDebug() << "4";
            return false;
        }
    }

    //check if lowerhull is completely below upperhull. THIS IS A WRONG CHECK!
    /*
     * QList<QGeoCoordinate> lower = QList<QGeoCoordinate>(lowerHull);
    lower.pop_back();
    lower.pop_front();
    if (!lower.isEmpty()) {
        std::sort(lower.begin(), lower.end(), compareLatitude);
        QGeoCoordinate highestOfLower = lower.back();
        foreach (QGeoCoordinate coordinate, upperHull) {
            if (coordinate.latitude() < highestOfLower.latitude()){
                qDebug() << "5";
                return false;
            }
        }
    }
    */

    return true;
}

QString GeoPolygon::toString()
{
    QString string = QString();
    foreach (QGeoCoordinate coordinate, coordinates) {
        string += (coordinate.toString(QGeoCoordinate::DegreesMinutesSeconds)) + (QString("   ||   "));
    }
    return string;
}

QGeoRectangle GeoPolygon::getBoundingQGeoRectangle()
{
    //Constructs a new geo rectangle,
    //of minimum size, containing all of the coordinates.
    //apparently not supported on jenkins, wtf.
    //return QGeoRectangle(coordinates);


    double west = getMostWestCoordinate().longitude();
    double east = getMostEastCoordinate().longitude();

    double north = -90.0;
    double south = 90.0;
    for (QGeoCoordinate coord : coordinates) {
        if (coord.latitude() > north)
            north = coord.latitude();
        if (coord.latitude() < south)
            south = coord.latitude();
    }
    return (QGeoRectangle(QGeoCoordinate(north, west), QGeoCoordinate(south, east)));

}

QList<QGeoCoordinate> GeoPolygon::getCoordinates() const
{
    return coordinates;
}

QList<QGeoCoordinate> GeoPolygon::getUpperHull() const
{
    return upperHull;
}

QList<QGeoCoordinate> GeoPolygon::getLowerHull() const
{
    return lowerHull;
}

QGeoCoordinate GeoPolygon::getMostWestCoordinate() const
{
    return mostWestCoordinate;
}

QGeoCoordinate GeoPolygon::getMostEastCoordinate() const
{
    return mostEastCoordinate;
}

double GeoPolygon::getArea() const
{
    return this->area;
}

void GeoPolygon::setArea(const double area)
{
    this->area = area;
}

QGeoCoordinate GeoPolygon::center() const
{
    return boundingBox().center();
}

QGeoRectangle GeoPolygon::boundingBox() const
{
    double topLat = -180, bottomLat = 180;
    for (QGeoCoordinate coord : coordinates) {
        if (coord.latitude() > topLat) {
            topLat = coord.latitude();
        } else if (coord.latitude() < bottomLat) {
            bottomLat = coord.latitude();
        }
    }

    QGeoRectangle boundingBox(
        QGeoCoordinate(topLat, mostWestCoordinate.longitude()),
        QGeoCoordinate(bottomLat, mostWestCoordinate.longitude())
    );
    return boundingBox;
}

