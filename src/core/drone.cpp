#include "drone.h"


Drone::Drone(): communicationLink(new Communication("127.0.0.1",45896))
{
    visionWidth = 1.0;


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
    delete communicationLink;
}


void Drone::startFlight()
{
    //Create json message to start the flight conform the interface of the wiki
    QJsonObject json = QJsonObject();
    json["MessageType"]= "control";
    json["Message"]= "start";
    QJsonDocument jsondoc(json);

    //send the json message
    communicationLink->doRequest(jsondoc.toJson(QJsonDocument::Indented));


}

void Drone::stopFlight()
{
    //Create json message to stop the flight conform the interface of the wiki
    QJsonObject json = QJsonObject();
    json["MessageType"]= "control";
    json["Message"]= "stop";
    QJsonDocument jsondoc(json);

    //send the json message
    communicationLink->doRequest(jsondoc.toJson(QJsonDocument::Indented));


}

void Drone::emergencyLanding()
{
    //Create json message to make an emergency landing conform the interface of the wiki
    QJsonObject json = QJsonObject();
    json["MessageType"]= "control";
    json["Message"]= "emergency";
    QJsonDocument jsondoc(json);

    //send the json message
    communicationLink->doRequest(jsondoc.toJson(QJsonDocument::Indented));
}


void Drone::sendWaypoints()
{
    //Create json message
    QJsonObject json = QJsonObject();
    json["MessageType"]= "control";
    json["Message"]= "path";

    QJsonArray coordinates = QJsonArray();
    foreach (const QGeoCoordinate waypoint, this->waypoints) {
            QJsonObject coordinate = QJsonObject();

            QJsonObject location = QJsonObject();
            location["Latitude"]= waypoint.latitude();
            location["Longitude"]= waypoint.longitude();

            coordinate["Location"] = location;
            coordinate["Order"]= 1;

            coordinates.append(coordinate);
    }
    json["Waypoints"] = coordinates;



    QJsonDocument jsondoc(json);

    //send the json message
    communicationLink->doRequest(jsondoc.toJson(QJsonDocument::Indented));
}
