#ifndef GEOUTILS_H
#define GEOUTILS_H
#include <cstdlib>
#include <math.h>
#include <vector>
#include <iostream>

using namespace std;
std::pair<double,double> changeLatitude(std::pair<double,double> coordinate, double distance);
std::pair<double,double> changeLongitude(std::pair<double,double> coordinate, double distance);

#endif // GEOUTILS_H
