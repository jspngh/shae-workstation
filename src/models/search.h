#ifndef SEARCH_H
#define SEARCH_H
#include <QUuid>
#include <QTime>
#include <QList>
#include <QGeoRectangle>

#include "communication/dronemodule.h"


class Search
{
public:
    //constructors
    Search();
    //~Search();

    QTime getStartTime() const;

    Search(QUuid searchID, QTime start, QGeoRectangle area, int height, int gimbalAngle);

    //getters
    QUuid getSearchID() const;

    QGeoRectangle getArea() const;
    void setArea(const QGeoRectangle &value);

    QList<DroneModule *> *getDroneList() const;
    void setDroneList(QList<DroneModule *> *value);

    int getGimbalAngle() const;
    void setGimbalAngle(int value);

    int getHeight() const;
    void setHeight(int value);

private:
    QUuid searchID;
    QTime startTime;
    QGeoRectangle area;
    int height;
    int gimbalAngle;
    QList<DroneModule *> *droneList;
};

#endif // SEARCH_H
