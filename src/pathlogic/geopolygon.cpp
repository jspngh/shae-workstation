#include "geopolygon.h"
#include <algorithm>

GeoPolygon::GeoPolygon()
    :QGeoShape()
{
    mostWestCoordinate = QGeoCoordinate(0.0,0.0);
    mostEastCoordinate = QGeoCoordinate(0.0,1.0);
    lowerHull = QList<QGeoCoordinate>();
    upperHull = QList<QGeoCoordinate>();
    lowerHull.push_back(mostWestCoordinate);
    lowerHull.push_back(mostEastCoordinate);
    upperHull.push_back(mostWestCoordinate);
    upperHull.push_back(QGeoCoordinate(1.0,0.4));
    upperHull.push_back(QGeoCoordinate(1.0,0.6));
    upperHull.push_back(mostEastCoordinate);
    coordinates = fromHull(upperHull, lowerHull);

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
    this->coordinates = fromHull(upperHull, lowerHull);

}

QList<QGeoCoordinate> GeoPolygon::fromHull(QList<QGeoCoordinate> upper, QList<QGeoCoordinate> lower)
{
    QList<QGeoCoordinate> list = QList<QGeoCoordinate>(upper);
    QList<QGeoCoordinate> lowerlist = QList<QGeoCoordinate>(lower);
    //pop the back and front, since upperhull already should contain these.
    lowerlist.pop_back();
    lowerlist.pop_front();
    //start from the end of the lowerhull, and add it to coordinates to create a list in clockwise order.
    while(!lowerlist.empty()){
        list.append(lowerlist.back());
        lowerlist.pop_back();
    }
    return list;
}

int GeoPolygon::compare(const QGeoCoordinate left, const QGeoCoordinate right)
{
    if(left.longitude() == right.longitude())
        return left.latitude() < right.latitude();
    else return left.longitude() < right.longitude();
}

int GeoPolygon::compareLatitude(const QGeoCoordinate left, const QGeoCoordinate right)
{
    if(left.latitude() == right.latitude())
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
    QList<QGeoCoordinate> lower = QList<QGeoCoordinate>(lowerHull);
    lower.pop_back();
    lower.pop_front();
    std::sort(lower.begin(), lower.end(), compareLatitude);
    QGeoCoordinate highestOfLower = lower.back();
    foreach(QGeoCoordinate coordinate, upperHull){
        if(coordinate.latitude() < highestOfLower.latitude())
            return false;
    }


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
    //Constructs a new geo rectangle,
    //of minimum size, containing all of the coordinates.
    return QGeoRectangle(coordinates);
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
