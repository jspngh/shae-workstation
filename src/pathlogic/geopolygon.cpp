#include "geopolygon.h"
#include <algorithm>

GeoPolygon::GeoPolygon()
{

}

GeoPolygon::GeoPolygon(QList<QGeoCoordinate> coordinates)
{
    //TODO: set mostWestCoordinate and set mostEastCoordinate
    /*
    double minLongitude = 180;
    double maxLongitude = -180;

    foreach(QGeoCoordinate coordinate, coordinates){
        if(coordinate.longitude() > maxLongitude )
            maxLongitude = coordinate.longitude();
            mostEastCoordinate = coordinate;
        if(coordinate.longitude() < minLongitude)
            minLongitude = coordinate.longitude();
            mostWestCoordinate = coordinate;
    }
    */
    std::sort(coordinates.begin(), coordinates.end(), compare);
    mostWestCoordinate = coordinates.front();
    mostEastCoordinate = coordinates.back();

    //TODO: create upperhull and lowerhull
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
                            coordinates[i]) <= 0.0){
            upperHull.pop_back();
        }
        upperHull.push_back(coordinates[i]);

    }
    //TODO: set coordidnates





    //if not valid, just return default constructor
    if(!isValid()){
        qDebug()<< "The polygon area created is not valid, using the default constructor now instead";
        return GeoPolygon();
    }
}

int compare(const QGeoCoordinate left, const QGeoCoordinate right)
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
        if (coordinate.longitude() < mostWestCoordinate)
            return false;
        if(coordinate.longitude() > mostEastCoordinate)
            return false;
    }


    //mostleft and most right should be in both hulls at resp. front and back
    if(upperHull.front() != mostWestCoordinate || lowerHull.front() != mostWestCoordinate)
       return false;
    if(upperHull.back() != mostWestCoordinate || lowerHull.back() != mostWestCoordinate)
       return false;

    //TODO: check if upperhull curves clockwise

    //TODO: check if lowerhull curves counter-clockwise

    //TODO: check if lowerhull is completely below upperhull.



    return true;
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
