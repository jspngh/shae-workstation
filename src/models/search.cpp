#include "search.h"

Search::Search()
    : searchID(QUuid::createUuid()),
      height(DEFAULT_HEIGHT),
      gimbalAngle(DEFAULT_GIMBAL_ANGLE),
      fpsProcessing(DEFAULT_FPS),
      speed(DEFAULT_SPEED)
{
    // TODO set time
}

Search::~Search()
{
}

Search::Search(const Search &d)
{
    searchID = d.searchID,
    startTime = d.startTime,
    area = d.area;
    height = d.height;
    gimbalAngle = d.gimbalAngle;
    fpsProcessing = d.fpsProcessing;
    speed = d.speed;
}


Search::Search(QUuid searchID, QTime start, QGeoRectangle area, int height, int gimbalAngle, int fpsProcessing):
    searchID(searchID),
    startTime(start),
    area(area),
    height(height),
    gimbalAngle(gimbalAngle),
    fpsProcessing(fpsProcessing),
    speed(DEFAULT_SPEED)
{
}

Search::Search(QUuid searchID, QTime start, QGeoRectangle area, int height, double speed, int gimbalAngle, int fpsProcessing):
    searchID(searchID),
    startTime(start),
    area(area),
    height(height),
    gimbalAngle(gimbalAngle),
    fpsProcessing(fpsProcessing),
    speed(speed)
{
}


QTime Search::getStartTime() const
{
    return startTime;
}

void Search::setStartTime(QTime start)
{
    startTime = start;
}

QGeoRectangle Search::getArea() const
{
    return area;
}

void Search::setArea(const QGeoRectangle &value)
{
    area = value;
}

QList<DroneModule *> Search::getDroneList() const
{
    return droneList;
}

void Search::setDroneList(QList<DroneModule *> value)
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

void Search::setSearchID(QUuid value)
{
    searchID = value;
}

QUuid Search::getSearchID() const
{
    return searchID;
}

double Search::getSpeed() const
{
    return speed;
}

void Search::setSpeed(double value)
{
    speed = value;
}


