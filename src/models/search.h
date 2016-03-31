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
    Search();

    ~Search();

    QTime getStartTime() const;

    QGeoRectangle getArea() const;
    void setArea(const QGeoRectangle &value);

    QList<DroneModule *> *getDroneList() const;
    void setDroneList(QList<DroneModule *> *value);

    int getGimbalAngle() const;
    void setGimbalAngle(int value);

    int getHeight() const;
    void setHeight(int value);

    int getFpsProcessing() const;
    void setFpsProcessing(int value);

private:
    QUuid searchID;
    QTime startTime;
    QGeoRectangle area;
    int height;
    int gimbalAngle;
    int fpsProcessing;
    QList<DroneModule *> *droneList;
};

#endif // SEARCH_H
