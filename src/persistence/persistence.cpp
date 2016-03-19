#include "persistence.h"

Persistence::Persistence(QObject *parent):
    QObject(parent)
{
    projectShaeDatabase = QSqlDatabase::addDatabase("QSQLITE");
    projectShaeDatabase.setDatabaseName(QString("/home/vpolflie/Documents/Eerst_Master_Computer_Wetenschappen/Design_Project/workstation/src/persistence/projectShae.db"));

    if (!projectShaeDatabase.open())
    {
       qDebug() << "Error: connection with database fail";
    }
    else
    {
       qDebug() << "Database: connection ok";
    }

    dronedao = DroneDAO(&projectShaeDatabase);
    detectionresultdao = DetectionResultDAO(&projectShaeDatabase);
    dronestatusdao = DroneStatusDAO(&projectShaeDatabase);
    dronesearchdao = DroneSearchDAO(&projectShaeDatabase);
    searchdao = SearchDAO(&projectShaeDatabase);
    videosequencedao = VideoSequenceDAO(&projectShaeDatabase);
}

Persistence::~Persistence(){
    projectShaeDatabase.close();
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


