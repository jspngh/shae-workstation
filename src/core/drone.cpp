#include "drone.h"


Drone::Drone(): communicationLink(new Communication("127.0.0.1",45896))
{
    visionWidth = 1.0;


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
    communicationLink->doRequest(jsondoc.toJson(QJsonDocument::Compact));


}

void Drone::stopFlight()
{
    //Create json message to stop the flight conform the interface of the wiki
    QJsonObject json = QJsonObject();
    json["MessageType"]= "control";
    json["Message"]= "stop";
    QJsonDocument jsondoc(json);

    //send the json message
    communicationLink->doRequest(jsondoc.toJson(QJsonDocument::Compact));


}

void Drone::emergencyLanding()
{
    //Create json message to make an emergency landing conform the interface of the wiki
    QJsonObject json = QJsonObject();
    json["MessageType"]= "control";
    json["Message"]= "emergency";
    QJsonDocument jsondoc(json);

    //send the json message
    communicationLink->doRequest(jsondoc.toJson(QJsonDocument::Compact));
}

//Still to do
void Drone::sendWaypoints()
{

}
