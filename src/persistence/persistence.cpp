#include "persistence.h"

Persistence::Persistence(QObject *parent):
    QObject(parent)
{
}

Search Persistence::saveSearch(Search &search)
{
    //TODO
    throw "Error: method not implemented yet.";
}

Search Persistence::retrieveSearch(QUuid searchId)
{
    //TODO
    throw "Error: method not implemented yet.";
}

DroneStatus Persistence::saveDroneStatus(DroneStatus &droneStatus, QUuid droneId, QUuid searchId)
{
    //TODO
    throw "Error: method not implemented yet.";
}

QList<DroneStatus> Persistence::retrieveDroneStatus(QUuid droneId, QUuid searchId, QTime begin, QTime end)
{
    //TODO
    throw "Error: method not implemented yet.";
}

DroneStatus Persistence::retrieveDroneStatus(QUuid droneId, QUuid searchId)
{
    //TODO
    throw "Error: method not implemented yet.";
}

DroneStatus Persistence::retrieveDroneStatus(QUuid droneId, QUuid searchId, QTime time)
{
    //TODO
    throw "Error: method not implemented yet.";
}

QList<QGeoCoordinate> Persistence::saveDronePath(QUuid droneId, QUuid searchId, QList<QGeoCoordinate> path)
{
    //TODO
    throw "Error: method not implemented yet.";
}

QList<QGeoCoordinate> Persistence::retrieveDronePath(QUuid droneId, QUuid searchId)
{
    //TODO
    throw "Error: method not implemented yet.";
}

VideoSequence saveVideoSequence(QUuid droneId, QUuid searchId, VideoSequence &sequence)
{
    //TODO
    throw "Error: method not implemented yet.";
}

VideoSequence retrieveVideoSequence(QUuid droneId, QUuid searchId, QUuid videoId)
{
    //TODO
    throw "Error: method not implemented yet.";
}

DetectionResult saveDetectionResult(QUuid droneId, QUuid searchId, DetectionResult &result)
{
    //TODO
    throw "Error: method not implemented yet.";
}

QList<DetectionResult> retrieveDetectionResults(QUuid droneId, QUuid searchId)
{
    //TODO
    throw "Error: method not implemented yet.";
}


