#include "drone.h"


Drone::Drone()
{
    visionWidth = 0.000001;


}

Drone::Drone(Communication* commlink, double vision): communicationLink(commlink)
{
    visionWidth = vision;


}

Drone::Drone(double visionWidth)
{
    Drone();
    if(visionWidth > MIN_VISIONWIDTH)
        this->visionWidth = visionWidth;
    else
        this ->visionWidth = MIN_VISIONWIDTH;
}

Drone::~Drone()
{

}

/***********************
Navigation message methods
************************/

QJsonDocument Drone::startFlight()
{
    //Create json message to start the flight conform the interface of the wiki
    QJsonObject json = QJsonObject();

    json["Message"]= "start";
    json["MessageType"]= "navigation";
    QJsonDocument jsondoc(json);


    //send the json message
    communicationLink->doRequest(jsondoc.toJson(QJsonDocument::Indented));

    return jsondoc;
}

QJsonDocument Drone::stopFlight()
{
    //Create json message to stop the flight conform the interface of the wiki
    QJsonObject json = QJsonObject();

    json["Message"]= "stop";
    json["MessageType"]= "navigation";
    QJsonDocument jsondoc(json);

    //send the json message
    communicationLink->doRequest(jsondoc.toJson(QJsonDocument::Indented));

    return jsondoc;
}

QJsonDocument Drone::emergencyLanding()
{
    //Create json message to make an emergency landing conform the interface of the wiki
    QJsonObject json = QJsonObject();

    json["Message"]= "emergency";
    json["MessageType"]= "navigation";
    QJsonDocument jsondoc(json);

    //send the json message
    communicationLink->doRequest(jsondoc.toJson(QJsonDocument::Indented));
    return jsondoc;
}


QJsonDocument Drone::sendWaypoints()
{
    //Create json message
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

    //send the json message
    communicationLink->doRequest(jsondoc.toJson(QJsonDocument::Indented));
    return jsondoc;
}

/**************************
Status messages method
**************************/
QJsonDocument Drone::requestStatus(DroneStatus status)
{
    std::list<DroneStatus> list = std::list<DroneStatus>();
    list.push_back(status);
    return requestStatuses(list);

}

QJsonDocument Drone::requestStatuses(std::list<DroneStatus> statuses)
{
    //Create json message
    QJsonObject json = QJsonObject();
    json["MessageType"]= "status";
    QJsonArray requestedStatuses = QJsonArray();
    foreach (const DroneStatus status, statuses){
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
        default:
            key = "current_lcoation";
            break;
        }
        requestedStatus["Key"] = key;
        requestedStatuses.append(requestedStatus);
    }
    json["Message"] = requestedStatuses;
    QJsonDocument jsondoc(json);

    //send
    communicationLink->doRequest(jsondoc.toJson(QJsonDocument::Indented));
    return jsondoc;

}

QJsonDocument Drone::requestHeartbeat()
{
    //Create json message
    QJsonObject json = QJsonObject();
    json["MessageType"] = "status";
    json["Message"] = "heartbeat";
    QJsonDocument jsondoc(json);

    //send
    communicationLink->doRequest(jsondoc.toJson(QJsonDocument::Indented));
    return jsondoc;
}


/**************************
Setting messages methods
**************************/

QJsonDocument Drone::setSetting(DroneSetting setting, int value)
{
    std::list<DroneSetting> settingList = std::list<DroneSetting>();
    settingList.push_back(setting);
    std::list<int> valueList = std::list<int>();
    valueList.push_back(value);

    return setSettings(settingList, valueList);
}

QJsonDocument Drone::setSettings(std::list<DroneSetting> settings, std::list<int> values)
{
    //Create json message
    QJsonObject json = QJsonObject();
    json["MessageType"]= "settings";
    QJsonArray settingsToSet = QJsonArray();
    int size = settings.size();
    for(int i=0; i < size ; i++){
        QJsonObject settingToSet = QJsonObject();
        QString key;
        DroneSetting setting = settings.front();
        settings.pop_front();
        switch (setting) {
        case Height:
            key = "height";
            break;
        case Speed:
            key = "speed";
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

    //send
    communicationLink->doRequest(jsondoc.toJson(QJsonDocument::Indented));
    return jsondoc;
}
