#include <QDebug>

#include "dronestatus.h"

DroneStatus::DroneStatus()
{

}

DroneStatus::~DroneStatus()
{
    // nothing needs to be deleted
}

DroneStatus::DroneStatus(const DroneStatus &droneStatus)
{
    drone = droneStatus.drone;
    orientation = droneStatus.orientation;
    cameraAngle = droneStatus.cameraAngle;
    speed = droneStatus.speed;
    selectedSpeed = droneStatus.selectedSpeed;
    height = droneStatus.height;
    selectedHeight = droneStatus.selectedHeight;
    batteryLevel = droneStatus.batteryLevel;
    droneState = droneStatus.droneState;
    fps = droneStatus.fps;
    resolution = droneStatus.resolution;
    heartbeat = droneStatus.heartbeat;
    manufacturer = droneStatus.manufacturer;
    type = droneStatus.type;
    timestampDrone = droneStatus.timestampDrone;
    currentLocation = droneStatus.currentLocation;
    nextWaypoint = droneStatus.nextWaypoint;
    previousWaypointOrder = droneStatus.previousWaypointOrder;
    nextWaypoints = droneStatus.nextWaypoints;
    timestampReceivedWorkstation = droneStatus.timestampReceivedWorkstation;
}

DroneStatus::DroneStatus(QDateTime timestampDrone, QDateTime timestampReceivedWorkstation, QGeoCoordinate location,
                         double orientation, double cameraAngle, double speed, double batteryLevel, int droneState):
    timestampDrone(timestampDrone),
    timestampReceivedWorkstation(timestampReceivedWorkstation),
    currentLocation(location),
    orientation(orientation),
    cameraAngle(cameraAngle),
    speed(speed),
    batteryLevel(batteryLevel),
    droneState(droneState)
{

}

DroneStatus::DroneStatus(QDateTime timestampDrone, QDateTime timestampReceivedWorkstation, QGeoCoordinate currentlocation,
                         double orientation, double cameraAngle, double speed, double selectedSpeed, double height,
                         double selectedHeight, double batteryLevel, int fps, int resolution, bool heartbeat,
                         int droneState, QString manufacturer, QString type, QGeoCoordinate nextWaypoint,
                         int previousWaypointOrder, QList<QGeoCoordinate> nextWaypoints):
    timestampDrone(timestampDrone),
    timestampReceivedWorkstation(timestampReceivedWorkstation),
    currentLocation(currentlocation),
    orientation(orientation),
    cameraAngle(cameraAngle),
    speed(speed),
    selectedSpeed(selectedSpeed),
    height(height),
    selectedHeight(selectedHeight),
    batteryLevel(batteryLevel),
    fps(fps),
    resolution(resolution),
    heartbeat(heartbeat),
    manufacturer(manufacturer),
    type(type),
    nextWaypoint(nextWaypoint),
    previousWaypointOrder(previousWaypointOrder),
    nextWaypoints(nextWaypoints),
    droneState(droneState)
{
}

DroneStatus DroneStatus::fromJsonString(QString string)
{
    //create status object to return and set current time
    DroneStatus status = DroneStatus();
    status.setTimestampRecievedWorkstation(QDateTime::currentDateTime());

    //Start parsing the string
    QJsonDocument jsondoc = QJsonDocument::fromJson(string.toUtf8());

    //not a Json message

    if (!jsondoc.isObject()) {
        qDebug() << "Not a Json object";
        throw ParseException("Not a Json object", string);
    }
    QJsonObject json = jsondoc.object();
    QString messageType = json["message_type"].toString();

    //not a status message
    if (messageType != "status") {
        qDebug() << "Not a status message";
        throw ParseException("Not a status message", string);
    }
    QJsonValue value = json["orientation"];
    if (! value.isUndefined()) {
        status.setOrientation(value.toDouble());
    }
    value = json["camera_angle"];
    if (! value.isUndefined()) {
        status.setCameraAngle(value.toDouble());
    }
    value = json["speed"];
    if (! value.isUndefined()) {
        status.setSpeed(value.toDouble());
    }
    value = json["selected_speed"];
    if (! value.isUndefined()) {
        status.setSelectedSpeed(value.toDouble());
    }
    value = json["battery_level"];
    if (! value.isUndefined()) {
        status.setBatteryLevel(value.toDouble());
    }
    value = json["drone_state"];
    if (! value.isUndefined()) {
        status.setDroneState(value.toInt());
    }
    value = json["fps"];
    if (! value.isUndefined()) {
        status.setFps(value.toInt());
    }
    value = json["heartbeat"];
    if (! value.isUndefined()) {
        status.setHeartbeat(value.toBool());
    }
    value = json["manufacturer"];
    if (! value.isUndefined()) {
        status.setManufacturer(value.toString());
    }
    value = json["type"];
    if (! value.isUndefined()) {
        status.setType(value.toString());
    }
    value = json["current_location"];
    if (! value.isUndefined() && value.isObject()) {
        QJsonObject position = value.toObject();
        status.setCurrentLocation(QGeoCoordinate(position["latitude"].toDouble(), position["longitude"].toDouble()));
    }
    value = json["next_waypoint"];
    if (! value.isUndefined() && value.isObject()) {
        QJsonObject position = value.toObject();
        status.setNextWaypoint(QGeoCoordinate(position["latitude"].toDouble(), position["longitude"].toDouble()));
    }
    value = json["next_waypoints"];
    if (! value.isUndefined() && value.isArray()) {
        QList<QGeoCoordinate> list = QList<QGeoCoordinate>();
        QJsonArray positions = value.toArray();
        for (auto v : positions) {
            QJsonObject position = v.toObject();
            list.push_back(QGeoCoordinate(position["latitude"].toDouble(), position["longitude"].toDouble()));
        }
        status.setNextWaypoints(list);
    }
    value = json["waypoint_order"];
    if (! value.isUndefined()) {
        status.setPreviousWaypointOrder(value.toInt());
    }
    value = json["timestamp"];
    if (! value.isUndefined()) {
        QString format = "ddmmyyyyHHmmsszzz"; //see http://doc.qt.io/qt-5/qdatetime.html#fromString
        status.setTimestampDrone(QDateTime::fromString(value.toString(), format));
    }

    return status;

}


/*****************
* Getters/Setters
*****************/

double DroneStatus::getOrientation() const
{
    return orientation;
}

void DroneStatus::setOrientation(double value)
{
    orientation = value;
}

double DroneStatus::getCameraAngle() const
{
    return cameraAngle;
}

void DroneStatus::setCameraAngle(double value)
{
    cameraAngle = value;
}

double DroneStatus::getSpeed() const
{
    return speed;
}

void DroneStatus::setSpeed(double value)
{
    speed = value;
}

double DroneStatus::getBatteryLevel() const
{
    return batteryLevel;
}

void DroneStatus::setBatteryLevel(double value)
{
    batteryLevel = value;
}

int DroneStatus::getDroneState() const
{
    return droneState;
}

void DroneStatus::setDroneState(int value)
{
    droneState = value;
}

QDateTime DroneStatus::getTimestampDrone() const
{
    return timestampDrone;
}

void DroneStatus::setTimestampDrone(const QDateTime &value)
{
    timestampDrone = value;
}

QDateTime DroneStatus::getTimestampRecievedWorkstation() const
{
    return timestampReceivedWorkstation;
}

void DroneStatus::setTimestampRecievedWorkstation(const QDateTime &value)
{
    timestampReceivedWorkstation = value;
}

double DroneStatus::getSelectedSpeed() const
{
    return selectedSpeed;
}

void DroneStatus::setSelectedSpeed(double value)
{
    selectedSpeed = value;
}

double DroneStatus::getHeight() const
{
    return height;
}

void DroneStatus::setHeight(double value)
{
    height = value;
}

double DroneStatus::getSelectedHeight() const
{
    return selectedHeight;
}

void DroneStatus::setSelectedHeight(double value)
{
    selectedHeight = value;
}

bool DroneStatus::getHeartbeat() const
{
    return heartbeat;
}

void DroneStatus::setHeartbeat(bool value)
{
    heartbeat = value;
}

QString DroneStatus::getManufacturer() const
{
    return manufacturer;
}

void DroneStatus::setManufacturer(const QString &value)
{
    manufacturer = value;
}

QString DroneStatus::getType() const
{
    return type;
}

void DroneStatus::setType(const QString &value)
{
    type = value;
}

QGeoCoordinate DroneStatus::getCurrentLocation() const
{
    return currentLocation;
}

void DroneStatus::setCurrentLocation(const QGeoCoordinate &value)
{
    currentLocation = value;
}

QGeoCoordinate DroneStatus::getNextWaypoint() const
{
    return nextWaypoint;
}

void DroneStatus::setNextWaypoint(const QGeoCoordinate &value)
{
    nextWaypoint = value;
}

int DroneStatus::getPreviousWaypointOrder() const
{
    return previousWaypointOrder;
}

void DroneStatus::setPreviousWaypointOrder(int value)
{
    previousWaypointOrder = value;
}

QList<QGeoCoordinate> DroneStatus::getNextWaypoints() const
{
    return nextWaypoints;
}

void DroneStatus::setNextWaypoints(const QList<QGeoCoordinate> &value)
{
    nextWaypoints = value;
}

int DroneStatus::getFps() const
{
    return fps;
}

void DroneStatus::setFps(int value)
{
    fps = value;
}

DroneModule *DroneStatus::getDrone() const
{
    return drone;
}

void DroneStatus::setDrone(DroneModule *value)
{
    drone = value;
}

int DroneStatus::getResolution() const
{
    return resolution;
}

void DroneStatus::setResolution(int value)
{
    resolution = value;
}

