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

class DroneStatus
{
public:
    DroneStatus();
    DroneStatus(const DroneStatus &d);
    ~DroneStatus();

    DroneStatus(QDateTime timestampDrone, QDateTime timestampReceiveWorkstation, QGeoCoordinate location,
                double orientation, double cameraAngle, double speed, double batteryLevel, int droneState);

    DroneStatus(QDateTime timestampDrone, QDateTime timestampReceiveWorkstation, QGeoCoordinate currentlocation,
                double orientation, double cameraAngle, double speed, double selectedSpeed, double height,
                double selectedHeight, double batteryLevel, int fps, int resolution, bool heartbeat,
                int droneState, QString manufacturer, QString type, QGeoCoordinate nextWaypoint,
                int previousWaypointOrder, QList<QGeoCoordinate> nextWaypoints);

    //! Creates a droneStatus object from a Json status messages that can be received from the drone.
    static DroneStatus fromJsonString(QString string);

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

    QDateTime getTimestampRecievedWorkstation() const;
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
    int resolution = -1;
    bool heartbeat = false;
    QString manufacturer = "";
    QString type = "";
    QDateTime timestampDrone;
    //! contains long, lat
    QGeoCoordinate currentLocation;
    QGeoCoordinate nextWaypoint;
    int previousWaypointOrder;
    QList<QGeoCoordinate> nextWaypoints;
    QDateTime timestampReceivedWorkstation;

};

Q_DECLARE_METATYPE(DroneStatus)

#endif // DRONESTATUS_H
