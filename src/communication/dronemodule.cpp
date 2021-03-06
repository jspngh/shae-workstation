#include "dronemodule.h"

#include "core/controller.h"
#include "models/search.h"


DroneModule::DroneModule()
// default configuration for a drone on the solo's network
    : DroneModule(6330, 5502, "10.1.1.10", "10.1.1.1", "10.1.1.179", "sololink")
{
}


DroneModule::DroneModule(int dataPort,
                         int streamPort,
                         QString droneIp,
                         QString controllerIp,
                         QString workstationIp,
                         QString streamPath,
                         double visionWidth,
                         bool video)
{
    drone = new Drone(dataPort, streamPort, droneIp, controllerIp, streamPath, visionWidth);
    droneConnection = new DroneConnection(droneIp, (quint16) dataPort);
    streamConnection = new StreamConnection(controllerIp, (quint16) streamPort);
    videoController = new VideoController();
    connectionThread = new QThread();
    streamThread = new QThread();
    videoThread = new QThread();
    this->workstationIp = workstationIp;
    waypoints = new QList<QGeoCoordinate>();
    droneConnection->moveToThread(connectionThread);
    streamConnection->moveToThread(streamThread);
    videoController->moveToThread(videoThread);
    connectionThread->start();
    streamThread->start();
    videoThread->start();
    videoProcessing = video;
    videoActive = false;
    isFlying = false;
    returningHome = false;
    detectionController = nullptr;
    connect(this, SIGNAL(droneRequest(QString)), droneConnection, SLOT(onDroneRequest(QString)), Qt::QueuedConnection);
    connect(this, SIGNAL(streamRequest()), streamConnection, SLOT(onStreamRequest()));

    connect(droneConnection, SIGNAL(droneResponse(const QString &)),
            this, SLOT(onDroneResponse(const QString &)));
    connect(droneConnection, SIGNAL(droneResponseError(int, const QString &)),
            this, SLOT(onDroneResponseError(int, const QString &)));
    // TODO: create a seperate onStreamError slot
    connect(streamConnection, SIGNAL(streamError(int, const QString &)),
            this, SLOT(onDroneResponseError(int, const QString &)));
    //connect the dronemodule with the corresponding videocontroller (should not occur via the mediator as it is an 1-1 relation)
    connect(this, SIGNAL(startStream(Drone *)), videoController, SLOT(onStartStream(Drone *)));
    connect(this, SIGNAL(stopStream(Drone *)), videoController, SLOT(onStopStream(Drone *)));
    connect(videoController, SIGNAL(streamStarted(QUuid, VideoSequence *)), this, SLOT(initDetection()));
}

DroneModule::DroneModule(const DroneModule &d)
{
}

DroneModule::~DroneModule()
{
    connectionThread->quit();
    connectionThread->wait();
    videoThread->quit();
    videoThread->wait();
    delete droneConnection;
    delete drone;
    delete connectionThread;
    delete videoController;
    delete videoThread;
    if (detectionController != nullptr) {
        delete detectionController;
    }
    if (heartbeatReceiver != nullptr)
        heartbeatReceiver->deleteLater();
    //TODO: delete waypoints fails if no waypoints assigned

}

/***********************
Getters/Setters
************************/

void DroneModule::setMediator(Mediator *med)
{
    mediator = med;
    videoController->setMediator(med);
    addSignalSlot();
    // initHeartbeat();
}

void DroneModule::addSignalSlot()
{
    qDebug() << "adding slots drone";
    mediator->addSignal(this, (char *) SIGNAL(landed(DroneModule *)), QString("landed(DroneModule*)"));
    mediator->addSignal(this, (char *) SIGNAL(startStreamWorkstation(DroneModule *)), QString("startStreamWorkstation(DroneModule*)"));
    mediator->addSignal(this, (char *) SIGNAL(droneStatusReceived(DroneStatus *)), QString("droneStatusReceived(DroneStatus*)"));
    mediator->addSignal(this, (char *) SIGNAL(droneHeartBeatReceived(DroneStatus *)), QString("droneHeartBeatReceived(DroneStatus*)"));
    mediator->addSlot(this, (char *) SLOT(onPathCalculated(Search *)), QString("pathCalculated(Search*)"));
    mediator->addSlot(this, (char *) SLOT(requestStatus()), QString("requestStatus()"));
    mediator->addSlot(this, (char *) SLOT(requestStatus(RequestedDroneStatus)), QString("requestStatus(RequestedDroneStatus)"));
    mediator->addSlot(this, (char *) SLOT(requestStatuses(QList<RequestedDroneStatus>)), QString("requestStatus(QList<RequestedDroneStatus>)"));
    mediator->addSlot(this, (char *) SLOT(requestHeartbeat()), QString("requestHeartbeart()"));
    mediator->addSlot(this, SLOT(onSearchEmitted(Search *)), QString("startSearch(Search*)"));

    connect(this, SIGNAL(droneStatusReceived(DroneStatus *)), this, SLOT(onDroneStatusReceived(DroneStatus *)));
    connect(this, SIGNAL(droneHeartBeatReceived(DroneStatus *)), this, SLOT(onDroneStatusReceived(DroneStatus *)));

}

void DroneModule::initHeartbeat()
{
    heartbeatReceiver = new DroneHeartBeatReceiver(workstationIp);

    connect(heartbeatReceiver, SIGNAL(droneHeartBeat(QString)),
            this, SLOT(onDroneResponse(QString)));
    connect(heartbeatReceiver, SIGNAL(droneHeartBeatError(int, QString)),
            this, SLOT(onDroneResponseError(int, QString)));

    setWorkstationConfiguration(workstationIp, heartbeatReceiver->getWorkstationHeartbeatPort());
}

DroneStatus DroneModule::getLastReceivedDroneStatus() const
{
    return lastReceivedDroneStatus;
}

QGeoCoordinate DroneModule::getHomeLocation() const
{
    return homeLocation;
}

PersistenceController *DroneModule::getPersistenceController() const
{
    return persistenceController;
}

void DroneModule::setPersistenceController(PersistenceController *value)
{
    persistenceController = value;
}

DetectionController *DroneModule::getDetectionController() const
{
    return detectionController;
}

void DroneModule::getStreamConnection()
{
    emit streamRequest();
}

void DroneModule::stopStreamConnection()
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


QUuid DroneModule::getGuid()
{
    QUuid id = drone->getGuid();
    return id;
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

void DroneModule::onDroneStatusReceived(DroneStatus *status)
{
    lastReceivedDroneStatus = *status;

    if (waypoints->size() != 0 &&
            status->getPreviousWaypointOrder() >= waypoints->size() - 1 &&
            status->getCurrentLocation().distanceTo(homeLocation) < 1 && !returningHome) {
        // the drone has finished it search and is back to its homelocation
        // issue drone to return to home (this is already done) and then land
        returnToHome();
    }

    if (status->getPreviousWaypointOrder() == 1 && videoProcessing && !videoActive) {
        qDebug() << "In first waypoint, starting stream";
        initStream();
        videoActive = true;
    }

    if (waypoints->size() != 0 && isFlying) {
        if (status->getPreviousWaypointOrder() == waypoints->size() - 1 && videoProcessing && videoActive) {
            videoActive = false;
            qDebug() << "In last waypoint, stopping stream";
            stopStream();
        }
    }

    if (returningHome && isFlying && status->getHeight() < h0 + 0.8) {
        isFlying = false;
        qDebug() << "drone has landed";
        emit landed(this);
    }

}

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
        QList<RequestedDroneSetting> settings = QList<RequestedDroneSetting>();
        settings.push_back(Height_To_Set);
        settings.push_back(Speed_To_Set);
        settings.push_back(Camera_Angle_To_Set);

        QList<int> values = QList<int>();
        values.push_back(s->getHeight());
        values.push_back(s->getSpeed());
        values.push_back(s->getGimbalAngle());


        setSettings(settings, values);
        usleep(3000);
        startFlight();
        usleep(10000);

        // add current drone location to waypoint queue to make waypoint loop 'closed'.
        homeLocation = lastReceivedDroneStatus.getCurrentLocation();
        getWaypoints()->append(homeLocation);

        sendWaypoints();
        usleep(3000);

        initHeartbeat();

        qDebug() << "Drone is starting flight";
    }
}

void DroneModule::onDroneResponse(const QString &response)
{
    QJsonDocument jsondoc = QJsonDocument::fromJson(response.toUtf8());

    if (!jsondoc.isObject()) {
        qDebug() << "Not a status or hearbeat :" << response;
        return;
    }

    DroneStatus status = DroneStatus::fromJsonString(response);
    status.setDrone(this);
    DroneStatus *status2 = new DroneStatus(status);

    if (status.getHeartbeat())
        emit droneHeartBeatReceived(status2);
    else
        emit droneStatusReceived(status2);
}

void DroneModule::onDroneResponseError(int socketError, const QString &message)
{
    qDebug() << "DroneResponseError received :" << message;
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

void DroneModule::initStream()
{
    emit startStream(drone);
    detectionController = new DetectionController(search, this, persistenceController);
    detectionController->setMediator(mediator);
}

void DroneModule::initDetection()
{
    detectionController->setPath(videoController->getSequencePath());
    detectionController->start();
}

void DroneModule::stopStream()
{
    emit stopStream(drone);
    detectionController->streamFinished();
    stopStreamConnection();
}

void DroneModule::onSearchEmitted(Search *s)
{
    search = s;
}

/***********************
Navigation message methods
************************/

QJsonDocument DroneModule::startFlight()
{
    h0 = lastReceivedDroneStatus.getHeight();
    isFlying = true;
    qDebug() << "height on take off: " << QString::number(h0);
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

QJsonDocument DroneModule::returnToHome()
{
    // Create json message to stop the flight conform the interface of the wiki
    QJsonObject json = QJsonObject();

    json["message"] = QString("rth");
    json["message_type"] = QString("navigation");
    QJsonDocument jsondoc(json);

    // Send the json message
    QString message = jsondoc.toJson(QJsonDocument::Indented);

    emit droneRequest(message);
    returningHome = true;

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
    foreach (const QGeoCoordinate waypoint, *waypoints) {
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
        case GPS_Count:
            key = "gps_signal";
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

