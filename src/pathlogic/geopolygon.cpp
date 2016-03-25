#include "geopolygon.h"
#include <algorithm>

GeoPolygon::GeoPolygon()
    :QGeoShape()
{

}

GeoPolygon::GeoPolygon(QList<QGeoCoordinate> coordinates)
    :QGeoShape()
{
    std::sort(coordinates.begin(), coordinates.end(), compare);
    mostWestCoordinate = coordinates.front();
    mostEastCoordinate = coordinates.back();

    //create upperhull and lowerhull
    int size = coordinates.size();
    lowerHull = QList<QGeoCoordinate>();
    for (int i = 0; i < size; ++i) {
        while (lowerHull.size() >= 2 &&
               crossProduct(lowerHull[lowerHull.size()-2],
                            lowerHull[lowerHull.size()-1],
                            coordinates[i]) <= 0.0){
            lowerHull.pop_back();
        }
        lowerHull.push_back(coordinates[i]);

    }

    upperHull = QList<QGeoCoordinate>();
    for (int i = 0; i < size; ++i) {
        while (upperHull.size() >= 2 &&
               crossProduct(upperHull[upperHull.size()-2],
                            upperHull[upperHull.size()-1],
                            coordinates[i]) >= 0.0){
            upperHull.pop_back();
        }
        upperHull.push_back(coordinates[i]);

    }
    this->coordinates = upperHull;

    QList<QGeoCoordinate> lower = QList<QGeoCoordinate>(lowerHull);
    lower.pop_back();
    lower.pop_front();
    this->coordinates.append(lower);





}

int GeoPolygon::compare(const QGeoCoordinate left, const QGeoCoordinate right)
{
    if(left.longitude() == right.longitude())
        return left.latitude() < right.latitude();
    else return left.longitude() < right.longitude();
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
    foreach(QGeoCoordinate coordinate, coordinates){
        if (coordinate.longitude() < mostWestCoordinate.longitude())
            return false;
        if(coordinate.longitude() > mostEastCoordinate.longitude())
            return false;
    }


    //mostleft and most right should be in both hulls at resp. front and back
    if(upperHull.front() != mostWestCoordinate)
       return false;
    if(lowerHull.front() != mostWestCoordinate)
        return false;
    if(upperHull.back() != mostEastCoordinate || lowerHull.back() != mostEastCoordinate)
       return false;

    //TODO: check if upperhull curves clockwise

    //TODO: check if lowerhull curves counter-clockwise

    //TODO: check if lowerhull is completely below upperhull.



    return true;
}

QString GeoPolygon::toString()
{
    QString string = QString();
    foreach(QGeoCoordinate coordinate, coordinates){
        string +=(coordinate.toString()) + (QString("   ||   "));
    }
    return string;
}

QGeoRectangle GeoPolygon::getBoundingQGeoRectangle()
{
    //TODO

    return QGeoRectangle();
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
