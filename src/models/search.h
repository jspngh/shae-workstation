#ifndef SEARCH_H
#define SEARCH_H
#include <QUuid>
#include <QTime>
#include "models/drone.h"


class Search
{
public:
    Search();
    QUuid searchID;
    QList<Drone> droneList;
    QTime start;
};

#endif // SEARCH_H
