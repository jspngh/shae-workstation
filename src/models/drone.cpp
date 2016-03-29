#include <QDebug>

#include "drone.h"
#include "core/controller.h"
#include "models/search.h"

Drone::Drone()
    : Drone(6331, "10.1.1.10", MIN_VISIONWIDTH)
{
}

Drone::Drone(int portNr, QString serverIp, double visionWidth):
    guid(QUuid::createUuid()),
    portNr(portNr),
    serverIp(serverIp),
    visionWidth(visionWidth)
{
    droneConnection = new DroneConnection(serverIp, (quint16) portNr);
    connectionThread = new QThread();
    droneConnection->moveToThread(connectionThread);
    connectionThread->start();

    connect(this, SIGNAL(droneRequest(QString)), droneConnection, SLOT(onDroneRequest(QString)), Qt::QueuedConnection);

    connect(droneConnection, SIGNAL(droneResponse(const QString &)),
                       this, SLOT(onDroneResponse(const QString &)));
    connect(droneConnection, SIGNAL(droneResponseError(int, const QString &)),
            this, SLOT(onDroneResponseError(int, const QString &)));
}

Drone::Drone(const Drone &d)
{
}

Drone::~Drone()
{
    connectionThread->quit();
    connectionThread->wait();
    delete droneConnection;
    delete connectionThread;
    //TODO: delete heartbeatReceiver;
    delete waypoints;
}

/***********************
Getters/Setters
************************/
void Drone::setController(Controller *c)
{
    controller = c;
    controller->getMediator()->addSlot(this, (char*) SLOT(onPathCalculated(Search *)), QString("pathCalculated(Search*)"));
    controller->getMediator()->addSignal(this, (char*) SIGNAL(droneStatusReceived(DroneStatus)), QString("droneStatusReceived(DroneStatus)"));
    controller->getMediator()->addSignal(this, (char*) SIGNAL(droneStatusReceived(DroneStatus)), QString("droneHeartbeatReceived(DroneStatus)"));

    heartbeatReceiver = new DroneHeartBeatReceiver(controller->getWorkstationIP());
    //heartbeatThread = new QThread();
    //heartbeatReceiver->moveToThread(heartbeatThread);
    //heartbeatThread->start();

    connect(heartbeatReceiver, SIGNAL(droneHeartBeat(QString)),
            this, SLOT(onDroneResponse(QString)));
    connect(heartbeatReceiver, SIGNAL(droneHeartBeatError(int,QString)),
            this, SLOT(onDroneResponseError(int,QString)));

    setWorkstationConfiguration(controller->getWorkstationIP(), heartbeatReceiver->getWorkstationHeartbeatPort());
}

QUuid Drone::getGuid() const
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

QList<QGeoCoordinate> *Drone::getWaypoints()
{
    return this->waypoints;
}

void Drone::setWaypoints(QList<QGeoCoordinate> *waypoints)
{
    this->waypoints = waypoints;
}

void Drone::addWaypoint(const QGeoCoordinate &waypoint)
{
    this->waypoints->push_back(waypoint);
}

double Drone::getVisionWidth() const
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
void Drone::onPathCalculated(Search *s)
{
    qDebug() << "Drone::onPathCalculated";
    bool droneInList = false;
    // check if this drone is selected for this search
    // if the drone is indeed selected we continue, if not, nothing will happen
    // Note: once the drone is found in the list, no need to continue searching (hence the '&& !droneSelected')
    for (int i = 0; i < s->getDroneList()->size() && !droneInList; i++)    {
        if (s->getDroneList()->at(i)->getGuid() == guid)
            droneInList = true;
    }
    if (droneInList) {
        // the drone is selected for this search
        qDebug() << "drone was selected";

        startFlight();
        qDebug() << "startFlight";
        sendWaypoints();
        qDebug() << "sendWaypoints";
    }
}

void Drone::onDroneResponse(const QString &response)
{
    qDebug() << "In processResponse";
    QJsonDocument jsondoc = QJsonDocument::fromJson(response.toUtf8());
    if (jsondoc.isObject()) {
        DroneStatus status = DroneStatus::fromJsonString(response);
        if (status.getHeartbeat())
            emit droneHeartBeatReceived(status);
        else
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

    emit droneRequest(message);
    qDebug() << "emit droneRequest(message)";
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

    emit droneRequest(message);

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

    emit droneRequest(message);
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
    foreach (const QGeoCoordinate waypoint, *waypoints) {
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
    QString message = jsondoc.toJson(QJsonDocument::Compact);

    emit droneRequest(message);
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

    emit droneRequest(message);
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

    emit droneRequest(message);
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

    emit droneRequest(message);
    return jsondoc;
}


/**************************
Setting messages methods
**************************/

QJsonDocument Drone::setWorkstationConfiguration(QString ipAdress, int port)
{
    // Create json message
    QJsonObject json = QJsonObject();
    json["MessageType"] = QString("settings");
    json["Message"] = QString("workstation_config");
    QJsonObject config = QJsonObject();
    config["IpAddress"] = ipAdress;
    config["Port"] = QString::number(port);
    json["Configuration"] = config;
    QJsonDocument jsondoc(json);

    // Send the json message
    QString message = jsondoc.toJson(QJsonDocument::Indented);

    emit droneRequest(message);
    return jsondoc;
}

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

    emit droneRequest(message);
    return jsondoc;
}
