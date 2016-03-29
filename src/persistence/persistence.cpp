#include "persistence.h"
#include <QDir>
#include <QFileInfo>
#include <QDebug>
#include <QStandardPaths>
#include <QSqlQuery>

Persistence::Persistence()
{
    initDatabase();
}

Persistence::Persistence(Mediator *mediator, QObject *parent):
    QObject(parent)
{
    Persistence::initDatabase();

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

void Persistence::initDatabase()
{
    bool dbNotCreatedYet = false;

    // Make sure the file exists
    QFileInfo checkFile(databaseLocation());
    if(!checkFile.exists() || !checkFile.isFile()) {
        // If not, create a file in which we will create the database
        QFile databaseFile(databaseLocation());
        databaseFile.open(QIODevice::ReadWrite);
        databaseFile.close();
        dbNotCreatedYet = true;
    }

    // Open database
    projectShaeDatabase = QSqlDatabase::addDatabase("QSQLITE");
    projectShaeDatabase.setDatabaseName(databaseLocation());

    if (!projectShaeDatabase.open())
       qDebug() << projectShaeDatabase.lastError();
    else
       qDebug() << "Database connection successfully setup.";

    if(dbNotCreatedYet) {
        createDatabase();
    }
}

QString Persistence::databaseLocation()
{
    QString folder = QStandardPaths::writableLocation(QStandardPaths::DataLocation);

    //create folder if not available
    QDir(QDir::root()).mkpath(folder);

    if(!folder.endsWith(QDir::separator()))
        folder.append(QDir::separator());

    QString name = "database.sqlite";

    return folder.append(name);
}

void Persistence::createDatabase()
{
    QFile sqlScheme(":/db/createTables.sql");
    if(sqlScheme.open(QIODevice::ReadOnly)) {
        QSqlQuery query(projectShaeDatabase);
        QStringList queryStrings = QTextStream(&sqlScheme).readAll().split(';');
        // Can't execute several queries at once, so split them
        // and execute them one by one.
        Q_FOREACH(QString queryString, queryStrings) {
            if(!query.exec(queryString))
                qDebug() << "Could not issue command: " << queryString;
        }
    } else {
        qDebug() << "Error opening file to create database";
    }
}

