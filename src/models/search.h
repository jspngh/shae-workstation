#ifndef SEARCH_H
#define SEARCH_H
#include <QUuid>
#include <QTime>
#include <QList>
#include <QGeoRectangle>
#include "communication/dronemodule.h"

/*!
 * \brief The Search class
 * \ingroup Models
 */
class Search
{
public:
    //constructors
    Search();
    Search(const Search &d);
    ~Search();

    Search(QUuid searchID, QTime start, QGeoRectangle area, int height, int gimbalAngle, int fpsProcessing);
    Search(QUuid searchID, QTime start, QGeoRectangle area, int height, double speed, int gimbalAngle, int fpsProcessing);

    QGeoRectangle getArea() const;
    void setArea(const QGeoRectangle &value);

    QList<DroneModule *> getDroneList() const;
    void setDroneList(QList<DroneModule *> value);

    QTime getStartTime() const;
    void setStartTime(QTime start);

    int getGimbalAngle() const;
    void setGimbalAngle(int value);

    int getHeight() const;
    void setHeight(int value);

    int getFpsProcessing() const;
    void setFpsProcessing(int value);

    void setSearchID(QUuid value);
    QUuid getSearchID() const;


    double getSpeed() const;
    void setSpeed(double value);

private:
    QUuid searchID;
    QTime startTime;
    QGeoRectangle area;
    int height;
    int gimbalAngle;
    QList<DroneModule *> droneList;
    int fpsProcessing;
    double speed;

    static constexpr int DEFAULT_HEIGHT = 3;
    static constexpr int DEFAULT_FPS = 1;
    static constexpr int DEFAULT_GIMBAL_ANGLE = 65;
    static constexpr double DEFAULT_SPEED = 2 ;
};

Q_DECLARE_METATYPE(Search)
#endif // SEARCH_H
