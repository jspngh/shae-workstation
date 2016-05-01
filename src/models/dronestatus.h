#ifndef DRONESTATUS_H
#define DRONESTATUS_H
#include <QString>
#include <QTime>
#include <QGeoCoordinate>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QString>
#include "communication/parseexception.h"

class DroneModule;

/*!
 * \brief The Dronestatus class is used for both heartbeat messages and status messages that
 * are exchanged between the drone and the workstation. The heartbeat message contains less data
 * and is exchanged more frequently. The status message contains all possible information
 * that the drone can provide.
 * \ingroup Models
 * This class represents the complete status of the drone and can hold a lot of different attributes.
 * A dronestatus object is created when receiving a heartbeat or a statusmessage from the drone.
 * Some fields might still have the default value, if they were not included in the message.
 */
class DroneStatus
{
public:
    /*!
     * \brief DroneStatus default constructor
     * Creates a default drone status.
     */
    DroneStatus();
    /*!
     * \brief DroneStatus copy constructor
     */
    DroneStatus(const DroneStatus &d);
    /*!
     * \brief DroneStatus destructor
     */
    ~DroneStatus();
    /*!
     * \brief default DroneStatus constructor of a heartbeat
     * \param timestampDrone is the timestamp of the drone, when the status message is generated.
     * \param timestampReceiveWorkstation is the timestamp of the workstation when the status message was received.
     * \param location is the location of the drone at the time of sending.
     * \param orientation is the orientation of the drone at the time of sending.
     * \param cameraAngle is the camera angle of the drone at the time of sending.
     * \param speed is the speed of the drone at the time of sending.
     * \param batteryLevel is the battery level of the drone at the time of sending.
     * \param droneState is the drone state at the time of sending (not used as for now).
    */
    DroneStatus(QDateTime timestampDrone, QDateTime timestampReceiveWorkstation, QGeoCoordinate location,
                double orientation, double cameraAngle, double speed, double batteryLevel, int droneState);
    /*!
     * \brief default DroneStatus constructor of a full status message
     * \param timestampDrone is the timestamp of the drone, when the status message is generated.
     * \param timestampReceiveWorkstation is the timestamp of the workstation when the status message was received.
     * \param location is the location of the drone at the time of sending.
     * \param orientation is the orientation of the drone at the time of sending.
     * \param cameraAngle is the camera angle of the drone at the time of sending.
     * \param selectedSpeed is the speed selected by the user.
     * \param selectedHeight is the height selected by the user.
     * \param height is the height of the drone at the time of sending.
     * \param batteryLevel is the battery level of the drone at the time of sending.
     * \param fps is the fps of the drone footage selected by the user.
     * \param resolution is the resolution of the drone footage selected by the user.
     * \param heartbeat is the boolean that indicates if the status message is a heartbeat.
     * \param manufacturer is the manufacturer of the drone.
     * \param type is the type of the drone.
     * \param nextWaypoint is the integer that indicates the waypoint to which the user is flying.
     * \param previousWaypointOrder is the last waypoint that the drone has reached.
     * \param nextWaypoints is the list of waypoints that the drone still has to fly to.
     * \param speed is the battery level of the drone at the time of sending.
     * \param droneState is the drone state at the time of sending (not used as for now).
    */
    DroneStatus(QDateTime timestampDrone, QDateTime timestampReceiveWorkstation, QGeoCoordinate location,
                double orientation, double cameraAngle, double speed, double selectedSpeed, double height,
                double selectedHeight, double batteryLevel, int fps, int resolution, bool heartbeat,
                int droneState, QString manufacturer, QString type, QGeoCoordinate nextWaypoint,
                int previousWaypointOrder, QList<QGeoCoordinate> nextWaypoints);

    //! Creates a droneStatus object from a Json status messages that can be received from the drone.
    //! This is the parsing method that is used everytime a status message or heartbeat is received ont he workstation.
    static DroneStatus fromJsonString(QString string);

    //! A method that makes a string containing sent timestamp, received timestamp and the location. This is used to display the status in the overview screen.
    QString toString() const;

    /*****************
    * Getters/Setters
    *****************/
    double getOrientation() const;
    void setOrientation(double value);

    double getCameraAngle() const;
    void setCameraAngle(double value);

    double getSpeed() const;
    void setSpeed(double value);

    double getBatteryLevel() const;
    void setBatteryLevel(double value);

    int getDroneState() const;
    void setDroneState(int value);

    QDateTime getTimestampDrone() const;
    void setTimestampDrone(const QDateTime &value);

    QDateTime getTimestampReceivedWorkstation() const;
    void setTimestampRecievedWorkstation(const QDateTime &value);

    double getSelectedSpeed() const;
    void setSelectedSpeed(double value);

    double getHeight() const;
    void setHeight(double value);

    double getSelectedHeight() const;
    void setSelectedHeight(double value);

    bool getHeartbeat() const;
    void setHeartbeat(bool value);

    QString getManufacturer() const;
    void setManufacturer(const QString &value);

    QString getType() const;
    void setType(const QString &value);

    QGeoCoordinate getCurrentLocation() const;
    void setCurrentLocation(const QGeoCoordinate &value);

    QGeoCoordinate getNextWaypoint() const;
    void setNextWaypoint(const QGeoCoordinate &value);

    int getPreviousWaypointOrder() const;
    void setPreviousWaypointOrder(int value);

    QList<QGeoCoordinate> getNextWaypoints() const;
    void setNextWaypoints(const QList<QGeoCoordinate> &value);

    int getFps() const;
    void setFps(int value);

    int getResolution() const;
    void setResolution(int value);

    DroneModule *getDrone() const;
    void setDrone(DroneModule *value);

    int getGpsCount() const;
    void setGpsCount(int value);

private:
    /**************
    * Attributes
    * Default values are values that are saved if the value was not received in the message.
    **************/


    DroneModule *drone; //!< pointer to the drone this status belongs
    double orientation = -1; //!< Orientation of the drone (0-360 degrees)
    double cameraAngle = -1; //!< the camera angle of the camera of the drone
    double speed = -1; //!< the speed of the drone in m/s
    double selectedSpeed = -1; //!< the speed that is selected for the drone
    double height = -1; //!< the height of the drone, in m
    double selectedHeight = -1; //!< the selected height that the drone should fly
    double batteryLevel = -1; //!< the current battery level of the drone
    int droneState = -1; //!< the state of the drone, see dronekit docs
    int fps = -1; //!< the speed at which the drone should film.
    int gpsCount = -1; //!< the number of GPS sattelites visible to the drone
    int resolution = -1; //!< the resolution in which the drone should film
    bool heartbeat = false; //!< a bool that says if this status is a heartbeat or a requested answer to a certain message
    QString manufacturer = ""; //!< the manufacturer of the drone, e.g. 3dr
    QString type = ""; //!< the type of the drone, e.g. solo
    QDateTime timestampDrone; //!< the time of the drone when this message was sent

    QGeoCoordinate currentLocation; //!< the lcoation of the drone

    QGeoCoordinate nextWaypoint; //!< the coordinate which the drone is flying to.
    int previousWaypointOrder; //!< the order of the previous waypoint. e.g. 4 when the drone is flying from the 4th to the 5th waypoint.
    QList<QGeoCoordinate> nextWaypoints; //!< a list of coordinates that the drone still has to fly
    QDateTime timestampReceivedWorkstation; //!< a timestamp generated by the workstation when receveiving this dronestatus

};

Q_DECLARE_METATYPE(DroneStatus)

#endif // DRONESTATUS_H
