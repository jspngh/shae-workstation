#include "GeoUtils.h"

/*! \file geo utility functions that allow to calculate geocoordinates based on a given coordinate and the distance in terms of longitude/latitude

*/

/*!
    \brief calculate a new geocoordinate based on an original coordinate, and the distance that is traversed.
    the distance is expressed in meters latitude (positive distance, being a distance in the north direction, negative distance being a distance in the south direction)

*/
std::pair<double, double> changeLatitude(std::pair<double, double> coordinate, double distance)
{
    double earthRadius = 6371000.0;
    double changeLatitude = (distance / earthRadius) * (180.0 / M_PI);

    return std::pair<double, double>(coordinate.first + changeLatitude, coordinate.second);
}

/*!
    \brief calculate a new geocoordinate based on an original coordinate, and the distance that is traversed.
    the distance is expressed in meters longitude (positive distance, being a distance in the east direction, negative distance being a distance in the west direction)

*/
std::pair<double, double> changeLongitude(std::pair<double, double> coordinate, double distance)
{
    double earthRadius = 6371000.0;
    double radius = earthRadius * cos(coordinate.first * (M_PI / 180.0));
    double changeLongitude = (distance / radius) * (180.0 / M_PI);

    return std::pair<double, double>(coordinate.first, coordinate.second + changeLongitude);
}
