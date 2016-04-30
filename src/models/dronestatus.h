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
    static DroneStatus fromJsonString(QString string);

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

    /*! Orientation (0-360 degrees)
     * Default as -1 */
    DroneModule *drone;
    double orientation = -1;
    double cameraAngle = -1;
    double speed = -1;
    double selectedSpeed = -1;
    double height = -1;
    double selectedHeight = -1;
    double batteryLevel = -1;
    int droneState = -1;
    int fps = -1;
    int gpsCount = -1;
    int resolution = -1;
    bool heartbeat = false;
    QString manufacturer = "";
    QString type = "";
    QDateTime timestampDrone;
    //! contains long, lat
    QGeoCoordinate currentLocation;
    //! contains the number of the waypoint it is flying to
    QGeoCoordinate nextWaypoint;
    int previousWaypointOrder;
    QList<QGeoCoordinate> nextWaypoints;
    QDateTime timestampReceivedWorkstation;

};

Q_DECLARE_METATYPE(DroneStatus)

#endif // DRONESTATUS_H
