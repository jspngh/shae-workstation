#ifndef SEARCH_H
#define SEARCH_H
#include <QUuid>
#include <QTime>
#include <QList>
#include <QGeoRectangle>
#include "communication/dronemodule.h"

/*!
 * \brief The Search class contains the different parameters for a search.
 * This class is used by different components in order to obtain the correct parameters.
 * \ingroup Models
 */
class Search
{
public:
    /*!
     * \brief Search default constructor
     * Creates a default Search.
     */
    Search();
    /*!
     * \brief Search copy constructor
     */
    Search(const Search &d);
    /*!
     * \brief Search destructor
     */
    ~Search();
    /*!
     * \brief default Search constructor
     * \param searchID, unique id of the search.
     * \param start, the starttime of the search.
     * \param area, the searcharea.
     * \param height, height of the drone in the search.
     * \param gimbalAngle, gimbal angle of the drone in the search
     * \param fpsProcessing, fps at which the drone stream is processed
     */
    Search(QUuid searchID, QTime start, QGeoRectangle area, int height, int gimbalAngle, int fpsProcessing);
    /*!
     * \brief default Search constructor
     * \param searchID, unique id of the search.
     * \param start, the starttime of the search.
     * \param area, the searcharea.
     * \param height, height of the drone in the search.
     * \param speed, speed of the drone in the search.
     * \param gimbalAngle, gimbal angle of the drone in the search
     * \param fpsProcessing, fps at which the drone stream is processed
     */
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
