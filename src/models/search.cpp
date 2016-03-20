#include "search.h"

Search::Search()
{

}

Search::Search(QUuid searchID, QTime start){
    this->searchID = searchID;
    this->start = start;
}

QUuid Search::getSearchID()
{
    return searchID;
}

//QList<Drone> Search::getDroneList()
//{
    //return droneList;
//}

QTime Search::getStart()
{
    return start;
}
