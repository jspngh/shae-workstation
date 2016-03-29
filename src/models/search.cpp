#include "search.h"

Search::Search()
    : searchID(QUuid::createUuid())
{
    // TODO set time
    //droneList = new QList<Drone*>;
}

/*Search::~Search()
{
    delete droneList;
}*/

Search::Search(QUuid searchID, QTime start){
    this->searchID = searchID;
    this->startTime = start;
    //droneList = new QList<Drone*>;
}

QUuid Search::getSearchID()
{
    return searchID;
}

//QList<Drone> Search::getDroneList()
//{
    //return droneList;
//}


QTime Search::getStartTime() const
{
    return startTime;
}

QGeoRectangle Search::getArea() const
{
    return area;
}

void Search::setArea(const QGeoRectangle &value)
{
    area = value;
}

QList<Drone *> *Search::getDroneList() const
{
    return droneList;
}

void Search::setDroneList(QList<Drone *> *value)
{
    droneList = value;
}
