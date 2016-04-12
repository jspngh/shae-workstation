#include "dronemodule.h"

#include <QDebug>

#include "core/controller.h"
#include "models/search.h"

DroneModule::DroneModule()
    // default configuration for a drone on the solo's network
    : DroneModule(6330, 5502, "10.1.1.10", "10.1.1.1", "10.1.1.179", "sololink.sdp", MIN_VISIONWIDTH)
{
}

DroneModule::DroneModule(int dataPort,
                         int streamPort,
                         QString droneIp,
                         QString controllerIp,
                         QString workstationIp,
                         QString streamPath,
                         double visionWidth)
{
    drone = new Drone(dataPort, streamPort, droneIp, controllerIp, streamPath, visionWidth);
    droneConnection = new DroneConnection(droneIp, (quint16) dataPort);
    streamConnection = new StreamConnection(controllerIp, (quint16) streamPort);
    connectionThread = new QThread();
    streamThread = new QThread();
    this->workstationIp = workstationIp;
    droneConnection->moveToThread(connectionThread);
    streamConnection->moveToThread(streamThread);
    connectionThread->start();
    streamThread->start();
    videoController = new VideoController();
    connect(this, SIGNAL(droneRequest(QString)), droneConnection, SLOT(onDroneRequest(QString)), Qt::QueuedConnection);
    connect(this, SIGNAL(streamRequest()), streamConnection, SLOT(onStreamRequest()));

    connect(droneConnection, SIGNAL(droneResponse(const QString &)),
            this, SLOT(onDroneResponse(const QString &)));
    connect(droneConnection, SIGNAL(droneResponseError(int, const QString &)),
            this, SLOT(onDroneResponseError(int, const QString &)));
    // TODO: create a seperate onStreamError slot
    connect(streamConnection, SIGNAL(streamError(int, const QString &)),
            this, SLOT(onDroneResponseError(int, const QString &)));
}

DroneModule::DroneModule(const DroneModule &d)
{
}

DroneModule::~DroneModule()
{
    connectionThread->quit();
    connectionThread->wait();
    delete droneConnection;
    delete drone;
    delete connectionThread;
    delete videoController;
    if(heartbeatReceiver)
            heartbeatReceiver->deleteLater();
    //TODO: delete waypoints fails if no waypoints assigned

}

/***********************
Getters/Setters
************************/

void DroneModule::setMediator(Mediator* med)
{
    mediator = med;

    med->addSlot(this, (char *) SLOT(onPathCalculated(Search *)), QString("pathCalculated(Search*)"));
    med->addSignal(this, (char *) SIGNAL(droneStatusReceived(DroneStatus)), QString("droneStatusReceived(DroneStatus)"));
    med->addSignal(this, (char *) SIGNAL(droneHeartBeatReceived(DroneStatus)), QString("droneHeartBeatReceived(DroneStatus)"));
    med->addSlot(this, (char *) SLOT(requestStatus()), QString("requestStatus()"));
    med->addSlot(this, (char *) SLOT(requestStatus(RequestedDroneStatus)), QString("requestStatus(RequestedDroneStatus)"));
    med->addSlot(this, (char *) SLOT(requestStatuses(QList<RequestedDroneStatus>)), QString("requestStatus(QList<RequestedDroneStatus>)"));
    med->addSlot(this, (char *) SLOT(requestHeartbeat()), QString("requestHeartbeart()"));

    heartbeatReceiver = new DroneHeartBeatReceiver(workstationIp);
    //heartbeatThread = new QThread();
    //heartbeatReceiver->moveToThread(heartbeatThread);
    //heartbeatThread->start();

    connect(heartbeatReceiver, SIGNAL(droneHeartBeat(QString)),
            this, SLOT(onDroneResponse(QString)));
    connect(heartbeatReceiver, SIGNAL(droneHeartBeatError(int, QString)),
            this, SLOT(onDroneResponseError(int, QString)));

    setWorkstationConfiguration(workstationIp, heartbeatReceiver->getWorkstationHeartbeatPort());

    DroneStatus droneStatus;
    droneStatus.setDrone(this);

    emit droneStatusReceived(droneStatus);
}

void DroneModule::getStream()
{
    qDebug() << "DroneModule:: getting stream";
    emit streamRequest();
}

void DroneModule::stopStream()
{
    streamConnection->stopConnection();
}

Drone *DroneModule::getDrone()
{
    return drone;
}

void DroneModule::setDrone(Drone *value)
{
    drone = value;
}


QUuid DroneModule::getGuid() const
{
    return drone->getGuid();
}

int DroneModule::getDronePort()
{
    return drone->getDronePort();
}

int DroneModule::getStreamPort()
{
    return drone->getStreamPort();
}

QString DroneModule::getDroneIp()
{
    return drone->getDroneIp();
}

QString DroneModule::getControllerIp()
{
    return drone->getControllerIp();
}

double DroneModule::getVisionWidth() const
{
    return drone->getVisionWidth();
}

void DroneModule::setVisionWidth(double visionWidth)
{
    drone->setVisionWidth(visionWidth);
}

QList<QGeoCoordinate> *DroneModule::getWaypoints()
{
    return this->waypoints;
}

void DroneModule::setWaypoints(QList<QGeoCoordinate> *waypoints)
{
    this->waypoints = waypoints;
}

void DroneModule::addWaypoint(const QGeoCoordinate &waypoint)
{
    this->waypoints->push_back(waypoint);
}


/***********************
Slots
************************/
void DroneModule::onPathCalculated(Search *s)
{
    bool droneInList = false;
    // check if this drone is selected for this search
    // if the drone is indeed selected we continue, if not, nothing will happen
    // Note: once the drone is found in the list, no need to continue searching (hence the '&& !droneSelected')
    for (int i = 0; i < s->getDroneList().size() && !droneInList; i++)    {
        if (s->getDroneList().at(i)->getGuid() == drone->getGuid())
            droneInList = true;
    }
    if (droneInList) {
        // the drone is selected for this search
        startFlight();
        sendWaypoints();
    }
}

void DroneModule::onDroneResponse(const QString &response)
{
    qDebug() << "In processResponse";
    QJsonDocument jsondoc = QJsonDocument::fromJson(response.toUtf8());
    if (jsondoc.isObject()) {
        DroneStatus status = DroneStatus::fromJsonString(response);
        status.setDrone(this);
        if (status.getHeartbeat()) {
            qDebug() << "emit DroneModule::droneHeartBeatReceived(status)";
            emit droneHeartBeatReceived(status);
        } else {
            qDebug() << "emit DroneModule::droneStatusReceived(status)";
            emit droneStatusReceived(status);
        }

    } else
        qDebug() << response;
}

void DroneModule::onDroneResponseError(int socketError, const QString &message)
{
    qDebug() << message;
}

DroneConnection *DroneModule::getDroneConnection() const
{
    return droneConnection;
}

DroneHeartBeatReceiver *DroneModule::getHeartbeatReceiver() const
{
    return heartbeatReceiver;
}

VideoController *DroneModule::getVideoController() const
{
    return videoController;
}

void DroneModule::setVideoController(VideoController *value)
{
    videoController = value;
}


/***********************
Navigation message methods
************************/

QJsonDocument DroneModule::startFlight()
{
    // Create json message to start the flight conform the interface of the wiki
    QJsonObject json = QJsonObject();

    json["message"] = QString("start");
    json["message_type"] = QString("navigation");
    QJsonDocument jsondoc(json);

    // Send the json message
    QString message = jsondoc.toJson(QJsonDocument::Indented);

    emit droneRequest(message);
    return jsondoc;
}

QJsonDocument DroneModule::stopFlight()
{
    // Create json message to stop the flight conform the interface of the wiki
    QJsonObject json = QJsonObject();

    json["message"] = QString("stop");
    json["message_type"] = QString("navigation");
    QJsonDocument jsondoc(json);

    // Send the json message
    QString message = jsondoc.toJson(QJsonDocument::Indented);

    emit droneRequest(message);

    return jsondoc;
}

QJsonDocument DroneModule::emergencyLanding()
{
    // Create json message to make an emergency landing conform the interface of the wiki
    QJsonObject json = QJsonObject();

    json["message"] = QString("emergency");
    json["message_type"] = QString("navigation");
    QJsonDocument jsondoc(json);


    // Send the json message
    QString message = jsondoc.toJson(QJsonDocument::Indented);

    emit droneRequest(message);
    return jsondoc;
}


QJsonDocument DroneModule::sendWaypoints()
{
    // Create json message
    QJsonObject json = QJsonObject();

    json["message"] = QString("path");
    json["message_type"] = QString("navigation");

    QJsonArray coordinates = QJsonArray();
    int i = 0;
    foreach(const QGeoCoordinate waypoint, *waypoints) {
        i++;
        QJsonObject coordinate = QJsonObject();

        QJsonObject location = QJsonObject();
        location["latitude"] = waypoint.latitude();
        location["longitude"] = waypoint.longitude();

        coordinate["location"] = location;
        coordinate["order"] = i;

        coordinates.append(coordinate);

    }
    json["waypoints"] = coordinates;
    QJsonDocument jsondoc(json);

    // Send the json message
    QString message = jsondoc.toJson(QJsonDocument::Indented);

    emit droneRequest(message);
    return jsondoc;
}

/**************************
Status messages method
**************************/
QJsonDocument DroneModule::requestStatus()
{
    //qDebug() << "DroneModule::requestStatus";
    // Create json message to request all statuses
    QJsonObject json = QJsonObject();

    json["message"] = QString("all_statuses");
    json["message_type"] = QString("status");
    QJsonDocument jsondoc(json);

    // Send the json message
    QString message = jsondoc.toJson(QJsonDocument::Indented);

    emit droneRequest(message);
    return jsondoc;
}


QJsonDocument DroneModule::requestStatus(RequestedDroneStatus status)
{
    QList<RequestedDroneStatus> list = QList<RequestedDroneStatus>();
    list.push_back(status);
    return requestStatuses(list);
}

QJsonDocument DroneModule::requestStatuses(QList<RequestedDroneStatus> statuses)
{
    // Create json message
    QJsonObject json = QJsonObject();
    json["message_type"] = QString("status");
    QJsonArray requestedStatuses = QJsonArray();
    foreach(const RequestedDroneStatus status, statuses) {
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
        case Waypoint_Order:
            key = "waypoint_order";
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
        requestedStatus["key"] = key;
        requestedStatuses.append(requestedStatus);
    }
    json["message"] = requestedStatuses;
    QJsonDocument jsondoc(json);

    // Send the json message
    QString message = jsondoc.toJson(QJsonDocument::Indented);

    emit droneRequest(message);
    return jsondoc;
}

QJsonDocument DroneModule::requestHeartbeat()
{
    // Create json message
    QJsonObject json = QJsonObject();
    json["message_type"] = QString("status");
    json["message"] = QString("heartbeat");
    QJsonDocument jsondoc(json);

    // Send the json message
    QString message = jsondoc.toJson(QJsonDocument::Indented);

    emit droneRequest(message);
    return jsondoc;
}


/**************************
Setting messages methods
**************************/

QJsonDocument DroneModule::setWorkstationConfiguration(QString ipAddress, int port)
{
    // Create json message
    QJsonObject json = QJsonObject();
    json["message_type"] = QString("settings");
    json["message"] = QString("workstation_config");
    QJsonObject config = QJsonObject();

    config["ip_address"] = ipAddress;

    config["port"] = QString::number(port);
    json["configuration"] = config;
    QJsonDocument jsondoc(json);

    // Send the json message
    QString message = jsondoc.toJson(QJsonDocument::Indented);

    emit droneRequest(message);
    return jsondoc;
}

QJsonDocument DroneModule::setSetting(RequestedDroneSetting setting, int value)
{
    QList<RequestedDroneSetting> settingList = QList<RequestedDroneSetting>();
    settingList.push_back(setting);
    QList<int> valueList = QList<int>();
    valueList.push_back(value);

    return setSettings(settingList, valueList);
}

QJsonDocument DroneModule::setSettings(QList<RequestedDroneSetting> settings, QList<int> values)
{
    // Create json message
    QJsonObject json = QJsonObject();
    json["message_type"] = QString("settings");
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
        settingToSet["key"] = key;
        settingToSet["value"] = values.front();
        values.pop_front();
        settingsToSet.append(settingToSet);
    }
    json["message"] = settingsToSet;
    QJsonDocument jsondoc(json);

    // Send the json message
    QString message = jsondoc.toJson(QJsonDocument::Indented);

    emit droneRequest(message);
    return jsondoc;
}
