#include <QDebug>

#include "drone.h"

Drone::Drone(Mediator *mediator)
{
    this->guid = QUuid::createUuid();
    this->portNr = 6330;
    this->serverIp = "10.1.1.10";
    this->visionWidth = MIN_VISIONWIDTH;
    droneConnection = new DroneConnection(mediator);

    connect(droneConnection, SIGNAL(droneResponse(const QString &)),
            this, SLOT(onDroneResponse(const QString &)));
    connect(droneConnection, SIGNAL(droneResponseError(int, const QString &)),
            this, SLOT(onDroneResponseError(int, const QString &)));
}

Drone::Drone(Mediator *mediator, QUuid guid, int portNr, QString serverIp, double visionWidth):
    guid(guid),
    portNr(portNr),
    serverIp(serverIp),
    visionWidth(visionWidth)
{
    droneConnection = new DroneConnection(mediator);

    auto res = connect(droneConnection, SIGNAL(droneResponse(const QString &)),
                       this, SLOT(onDroneResponse(const QString &)));
    connect(droneConnection, SIGNAL(droneResponseError(int, const QString &)),
            this, SLOT(onDroneResponseError(int, const QString &)));
}

Drone::~Drone()
{
    delete droneConnection;
}

/***********************
Getters/Setters
************************/
QUuid Drone::getGuid()
{
    return this->guid;
}

int Drone::getPortNr()
{
    return this->portNr;
}

QString Drone::getServerIp()
{
    return this->serverIp;
}

QList<QGeoCoordinate> &Drone::getWaypoints()
{
    return this->waypoints;
}

void Drone::setWaypoints(const QList<QGeoCoordinate> &waypoints)
{
    this->waypoints = waypoints;
}

void Drone::addWaypoint(const QGeoCoordinate &waypoint)
{
    this->waypoints.push_back(waypoint);
}

double Drone::getVisionWidth()
{
    return this->visionWidth;
}

void Drone::setVisionWidth(double visionWidth)
{
    this->visionWidth = visionWidth;
}

/***********************
Slots
************************/
void Drone::onDroneResponse(const QString &response)
{
    qDebug() << "In processResponse";
    QJsonDocument jsondoc = QJsonDocument::fromJson(response.toUtf8());
    if (jsondoc.isObject()) {
        DroneStatus status = DroneStatus::fromJsonString(response);
        emit droneStatusReceived(status);
    } else
        qDebug() << response;
}

void Drone::onDroneResponseError(int socketError, const QString &message)
{
    qDebug() << message;
}


/***********************
Navigation message methods
************************/

QJsonDocument Drone::startFlight()
{
    // Create json message to start the flight conform the interface of the wiki
    QJsonObject json = QJsonObject();

    json["Message"] = QString("start");
    json["MessageType"] = QString("navigation");
    QJsonDocument jsondoc(json);


    // Send the json message
    QString message = jsondoc.toJson(QJsonDocument::Indented);
    droneConnection->droneRequest(serverIp, (quint16) portNr, message);

    return jsondoc;
}

QJsonDocument Drone::stopFlight()
{
    // Create json message to stop the flight conform the interface of the wiki
    QJsonObject json = QJsonObject();

    json["Message"] = QString("stop");
    json["MessageType"] = QString("navigation");
    QJsonDocument jsondoc(json);

    // Send the json message
    QString message = jsondoc.toJson(QJsonDocument::Indented);
    droneConnection->droneRequest(serverIp, (quint16) portNr, message);

    return jsondoc;
}

QJsonDocument Drone::emergencyLanding()
{
    // Create json message to make an emergency landing conform the interface of the wiki
    QJsonObject json = QJsonObject();

    json["Message"] = QString("emergency");
    json["MessageType"] = QString("navigation");
    QJsonDocument jsondoc(json);


    // Send the json message
    QString message = jsondoc.toJson(QJsonDocument::Indented);
    droneConnection->droneRequest(serverIp, (quint16) portNr, message);

    return jsondoc;
}


QJsonDocument Drone::sendWaypoints()
{
    // Create json message
    QJsonObject json = QJsonObject();

    json["Message"] = QString("path");
    json["MessageType"] = QString("navigation");

    QJsonArray coordinates = QJsonArray();
    int i = 0;
    foreach (const QGeoCoordinate waypoint, this->waypoints) {
        i++;
        QJsonObject coordinate = QJsonObject();

        QJsonObject location = QJsonObject();
        location["Latitude"] = waypoint.latitude();
        location["Longitude"] = waypoint.longitude();

        coordinate["Location"] = location;
        coordinate["Order"] = i;

        coordinates.append(coordinate);

    }
    json["Waypoints"] = coordinates;
    QJsonDocument jsondoc(json);

    // Send the json message
    QString message = jsondoc.toJson(QJsonDocument::Indented);
    droneConnection->droneRequest(serverIp, (quint16) portNr, message);

    return jsondoc;
}

/**************************
Status messages method
**************************/
QJsonDocument Drone::requestStatus()
{
    // Create json message to request all statuses
    QJsonObject json = QJsonObject();

    json["Message"] = QString("all_statuses");
    json["MessageType"] = QString("status");
    QJsonDocument jsondoc(json);

    // Send the json message
    QString message = jsondoc.toJson(QJsonDocument::Indented);
    droneConnection->droneRequest(serverIp, (quint16) portNr, message);

    return jsondoc;
}


QJsonDocument Drone::requestStatus(RequestedDroneStatus status)
{
    QList<RequestedDroneStatus> list = QList<RequestedDroneStatus>();
    list.push_back(status);
    return requestStatuses(list);
}

QJsonDocument Drone::requestStatuses(QList<RequestedDroneStatus> statuses)
{
    // Create json message
    QJsonObject json = QJsonObject();
    json["MessageType"] = QString("status");
    QJsonArray requestedStatuses = QJsonArray();
    foreach (const RequestedDroneStatus status, statuses) {
        QJsonObject requestedStatus = QJsonObject();
        QString key;
        switch (status) {
        case Battery_Level:
            key = "battery_level";
            break;
        case Location:
            key = "current_location";
            break;
        case Drone_Type:
            key = "drone_type";
            break;
        case Waypoint_Reached:
            key = "waypoint_reached";
            break;
        case Speed:
            key = "speed";
            break;
        case Selected_Speed:
            key = "selected_speed";
            break;
        case Height:
            key = "height";
            break;
        case Selected_Height:
            key = "selected_height";
            break;
        case Camera_Angle:
            key = "camera_angle";
            break;
        case FPS:
            key = "fps";
            break;
        case Resolution:
            key = "resolution";
            break;
        case Next_Waypoint:
            key = "next_waypoint";
            break;
        case Next_Waypoints:
            key = "next_waypoints";
            break;

        default:
            key = "current_location";
            break;
        }
        requestedStatus["Key"] = key;
        requestedStatuses.append(requestedStatus);
    }
    json["Message"] = requestedStatuses;
    QJsonDocument jsondoc(json);

    // Send the json message
    QString message = jsondoc.toJson(QJsonDocument::Indented);
    droneConnection->droneRequest(serverIp, (quint16) portNr, message);

    return jsondoc;
}

QJsonDocument Drone::requestHeartbeat()
{
    // Create json message
    QJsonObject json = QJsonObject();
    json["MessageType"] = QString("status");
    json["Message"] = QString("heartbeat");
    QJsonDocument jsondoc(json);

    // Send the json message
    QString message = jsondoc.toJson(QJsonDocument::Indented);
    droneConnection->droneRequest(serverIp, (quint16) portNr, message);

    return jsondoc;
}


/**************************
Setting messages methods
**************************/

QJsonDocument Drone::setSetting(RequestedDroneSetting setting, int value)
{
    QList<RequestedDroneSetting> settingList = QList<RequestedDroneSetting>();
    settingList.push_back(setting);
    QList<int> valueList = QList<int>();
    valueList.push_back(value);

    return setSettings(settingList, valueList);
}

QJsonDocument Drone::setSettings(QList<RequestedDroneSetting> settings, QList<int> values)
{
    // Create json message
    QJsonObject json = QJsonObject();
    json["MessageType"] = QString("settings");
    QJsonArray settingsToSet = QJsonArray();
    int size = settings.size();
    for (int i = 0; i < size ; i++) {
        QJsonObject settingToSet = QJsonObject();
        QString key;
        RequestedDroneSetting setting = settings.front();
        settings.pop_front();
        switch (setting) {
        case Height_To_Set:
            key = "height";
            break;
        case Speed_To_Set:
            key = "speed";
            break;
        case Camera_Angle_To_Set:
            key = "camera_angle";
            break;
        case FPS_To_Set:
            key = "fps";
            break;
        case Resolution_To_Set:
            key = "resolution";
            break;
        default:
            key = "fps";
            break;
        }
        settingToSet["Key"] = key;
        settingToSet["Value"] = values.front();
        values.pop_front();
        settingsToSet.append(settingToSet);
    }
    json["Message"] = settingsToSet;
    QJsonDocument jsondoc(json);

    // Send the json message
    QString message = jsondoc.toJson(QJsonDocument::Indented);
    droneConnection->droneRequest(serverIp, (quint16) portNr, message);

    return jsondoc;
}
