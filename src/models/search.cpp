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

Search::Search(QUuid searchID, QTime start, QGeoRectangle area, int height, int gimbalAngle):
    searchID(searchID),
    startTime(start),
    area(area),
    height(height),
    gimbalAngle(gimbalAngle)
{
}

QUuid Search::getSearchID() const
{
    return searchID;
}

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

QList<DroneModule *> *Search::getDroneList() const
{
    return droneList;
}

void Search::setDroneList(QList<DroneModule *> *value)
{
    droneList = value;
}

int Search::getGimbalAngle() const
{
    return gimbalAngle;
}

void Search::setGimbalAngle(int value)
{
    gimbalAngle = value;
}

int Search::getHeight() const
{
    return height;
}

void Search::setHeight(int value)
{
    height = value;
}

int Search::getFpsProcessing() const
{
    return fpsProcessing;
}

void Search::setFpsProcessing(int value)
{
    fpsProcessing = value;
}
