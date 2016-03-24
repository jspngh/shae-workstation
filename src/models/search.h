#ifndef SEARCH_H
#define SEARCH_H
#include <QUuid>
#include <QTime>
#include <QList>
#include <QGeoRectangle>

#include "models/drone.h"


class Search
{
public:
    Search();

    ~Search();

    QTime getStartTime() const;

    QGeoRectangle getArea() const;
    void setArea(const QGeoRectangle &value);

    QList<Drone *> *getDroneList() const;
    void setDroneList(QList<Drone *> *value);

    double getGimbalAngle() const;
    void setGimbalAngle(double value);

    double getHeight() const;
    void setHeight(double value);

private:
    QUuid searchID;
    QTime startTime;
    QGeoRectangle area;
    QList<Drone *> *droneList;
    double height;
    double gimbalAngle;
};

#endif // SEARCH_H
