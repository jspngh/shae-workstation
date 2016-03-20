#include "persistence.h"

Persistence::Persistence(QObject *parent):
    QObject(parent)
{
    projectShaeDatabase = QSqlDatabase::addDatabase("QSQLITE");
    projectShaeDatabase.setDatabaseName("/home/vpolflie/Documents/Eerst_Master_Computer_Wetenschappen/Design_Project/workstation/src/persistence/projectShae.db");

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

void Persistence::saveSearch(Search &search)
{
    emit onSaveSearch(searchdao.dbSaveSearch(search));
}

void Persistence::retrieveSearch(QUuid searchId)
{
    emit onRetrieveSearch(searchdao.dbRetrieveSearch(searchId));
}

void Persistence::saveDroneStatus(DroneStatus &droneStatus, QUuid droneId, QUuid searchId)
{
    emit onSaveDroneStatus(dronestatusdao.dbSaveDroneStatus(droneStatus, droneId, searchId));
}

void Persistence::retrieveDroneStatus(QUuid droneId, QUuid searchId, QDateTime begin, QDateTime end)
{
    emit onRetrieveDroneStatus(dronestatusdao.dbRetrieveDroneStatus(droneId,searchId,begin,end));
}

void Persistence::retrieveDroneStatus(QUuid droneId, QUuid searchId)
{
    emit onRetrieveLatestDroneStatus(dronestatusdao.dbRetrieveDroneStatus(droneId,searchId));
}

void Persistence::retrieveDroneStatus(QUuid droneId, QUuid searchId, QDateTime time)
{
  emit onRetrieveClosestDroneStatus(dronestatusdao.dbRetrieveDroneStatus(droneId,searchId,time));
}

/*void Persistence::saveDrone(Drone drone)
{
    //TODO
    throw "Error: method not implemented yet.";
}

void Persistence::retrieveDrone(QUuid droneId)
{
    //TODO
    throw "Error: method not implemented yet.";
}*/

void Persistence::saveDronePath(QUuid droneId, QUuid searchId, QList<QGeoCoordinate> path)
{
    emit onSaveDronePath(dronesearchdao.dbSaveDronePath(droneId,searchId,path));
}

void Persistence::retrieveDronePath(QUuid droneId, QUuid searchId)
{
    emit onRetrieveDronePath(dronesearchdao.dbRetrieveDronePath(droneId, searchId));
}

void Persistence::saveVideoSequence(QUuid droneId, QUuid searchId, VideoSequence &sequence)
{
    emit onSaveVideoSequence(videosequencedao.dbSaveVideoSequence(droneId,searchId,sequence));
}

void Persistence::retrieveVideoSequence(QUuid droneId, QUuid searchId, QUuid videoId)
{
    emit onRetrieveVideoSequence(videosequencedao.dbRetrieveVideoSequence(droneId, searchId,videoId));
}

void Persistence::saveDetectionResult(QUuid droneId, QUuid searchId, DetectionResult &result)
{
    emit onSaveDetectionResult(detectionresultdao.dbSaveDetectionResult(droneId,searchId,result));
}

void Persistence::retrieveDetectionResults(QUuid droneId, QUuid searchId)
{
    emit onRetrieveDetectionResults(detectionresultdao.dbRetrieveDetectionResults(droneId,searchId));
}


