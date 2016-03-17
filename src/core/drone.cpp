#include <QDebug>

#include "drone.h"


Drone::Drone()
{
    this->guid = QUuid::createUuid();
    this->portNr = 6330;
    this->serverIp = "10.1.1.10";
    this->visionWidth = MIN_VISIONWIDTH;
    droneConnection = new DroneConnection();

    connect(droneConnection, SIGNAL(droneResponse(const QString &)),
            this, SLOT(processResponse(const QString &)));
    connect(droneConnection, SIGNAL(error(int,const QString &)),
            this, SLOT(processError(int,const QString &)));
}

Drone::Drone(QUuid guid, int portNr, QString serverIp, double visionWidth):
    guid(guid),
    portNr(portNr),
    serverIp(serverIp),
    visionWidth(visionWidth)
{
    droneConnection = new DroneConnection();

    auto res = connect(droneConnection, SIGNAL(droneResponse(const QString &)),
            this, SLOT(processResponse(const QString &)));
    connect(droneConnection, SIGNAL(error(int,const QString &)),
            this, SLOT(processError(int,const QString &)));
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

std::list<QGeoCoordinate>& Drone::getWaypoints()
{
    return this->waypoints;
}

void Drone::setWaypoints(const std::list<QGeoCoordinate> &waypoints)
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
void Drone::processResponse(const QString &response)
{
    qDebug() << "In processResponse";
    qDebug() << response;
}

void Drone::processError(int socketError, const QString &message)
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

    json["Message"]= "start";
    json["MessageType"]= "navigation";
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

    json["Message"]= "stop";
    json["MessageType"]= "navigation";
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

    json["Message"]= "emergency";
    json["MessageType"]= "navigation";
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

    json["Message"]= "path";
    json["MessageType"]= "navigation";

    QJsonArray coordinates = QJsonArray();
    int i=0;
    foreach (const QGeoCoordinate waypoint, this->waypoints) {
        i++;
        QJsonObject coordinate = QJsonObject();

        QJsonObject location = QJsonObject();
        location["Latitude"]= waypoint.latitude();
        location["Longitude"]= waypoint.longitude();

        coordinate["Location"] = location;
        coordinate["Order"]= i;

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

    json["Message"]= "allStatuses";
    json["MessageType"]= "status";
    QJsonDocument jsondoc(json);

    // Send the json message
    QString message = jsondoc.toJson(QJsonDocument::Indented);
    droneConnection->droneRequest(serverIp, (quint16) portNr, message);

    return jsondoc;
}


QJsonDocument Drone::requestStatus(RequestedDroneStatus status)
{
    std::list<RequestedDroneStatus> list = std::list<RequestedDroneStatus>();
    list.push_back(status);
    return requestStatuses(list);
}

QJsonDocument Drone::requestStatuses(std::list<RequestedDroneStatus> statuses)
{
    // Create json message
    QJsonObject json = QJsonObject();
    json["MessageType"]= "status";
    QJsonArray requestedStatuses = QJsonArray();
    foreach (const RequestedDroneStatus status, statuses){
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
    json["MessageType"] = "status";
    json["Message"] = "heartbeat";
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
    std::list<RequestedDroneSetting> settingList = std::list<RequestedDroneSetting>();
    settingList.push_back(setting);
    std::list<int> valueList = std::list<int>();
    valueList.push_back(value);

    return setSettings(settingList, valueList);
}

QJsonDocument Drone::setSettings(std::list<RequestedDroneSetting> settings, std::list<int> values)
{
    // Create json message
    QJsonObject json = QJsonObject();
    json["MessageType"]= "settings";
    QJsonArray settingsToSet = QJsonArray();
    int size = settings.size();
    for(int i=0; i < size ; i++){
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
