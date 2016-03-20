#ifndef SEARCH_H
#define SEARCH_H
#include <QUuid>
#include <QTime>
#include "models/drone.h"


class Search
{
public:
    //constructors
    Search();
    Search(QUuid searchID, QTime start);
    //getters
    QUuid getSearchID();
    //QList<Drone> getDroneList();
    QTime getStart();

private:
    QUuid searchID;
    //QList<Drone> droneList;
    QTime start;
};

#endif // SEARCH_H
