#ifndef SEARCH_H
#define SEARCH_H
#include <QUuid>
#include <QTime>
#include "core/models/drone.h"


class Search
{
public:
    Search();
    QUuid searchID;
    std::list<Drone> droneList;
    QTime start;
};

#endif // SEARCH_H
