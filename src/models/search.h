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

private:
    QUuid searchID;
    QTime startTime;
    QGeoRectangle area;
    QList<DroneModule *> *droneList;
};

#endif // SEARCH_H
