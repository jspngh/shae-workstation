#ifndef SEARCH_H
#define SEARCH_H
#include <QUuid>
#include <QTime>
#include "models/drone.h"


class Search
{
public:
    Search(double height, double gimBalAngle);
    QUuid searchID;
    QList<Drone> droneList;
    QTime start;
    double height;
    double gimbalAngle;
};

#endif // SEARCH_H
