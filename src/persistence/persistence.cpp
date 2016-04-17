#include "persistence.h"
#include <QDir>
#include <QFileInfo>
#include <QtDebug>
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

Persistence::~Persistence()
{
    projectShaeDatabase.close();
}

void Persistence::saveSearch(Search *search)
{
    searchdao.dbSaveSearch(search);
}

Search* Persistence::retrieveSearch(QUuid searchId)
{
    return searchdao.dbRetrieveSearch(searchId);
}

void Persistence::saveDroneStatus(DroneStatus *droneStatus)
{
    dronestatusdao.dbSaveDroneStatus(droneStatus);
}

QList<DroneStatus*>* Persistence::retrieveDroneStatus(QUuid droneId, QDateTime begin, QDateTime end)
{
    return dronestatusdao.dbRetrieveDroneStatus(droneId, begin, end);
}

DroneStatus* Persistence::retrieveDroneStatus(QUuid droneId)
{
    return dronestatusdao.dbRetrieveDroneStatus(droneId);
}

DroneStatus* Persistence::retrieveDroneStatus(QUuid droneId, QDateTime time)
{
    return dronestatusdao.dbRetrieveDroneStatus(droneId, time);
}

void Persistence::saveDrone(Drone *drone)
{
    dronedao.dbSaveDrone(drone);
}

Drone* Persistence::retrieveDrone(QUuid droneId)
{
    return dronedao.dbRetrieveDrone(droneId);
}

QList<QUuid>* Persistence::retrieveDroneIds(QUuid searchId)
{
    return dronesearchdao.dbRetrieveDroneIds(searchId);
}

void Persistence::saveDronePath(QUuid droneId, QUuid searchId, QList<QGeoCoordinate> *path)
{
    dronesearchdao.dbSaveDronePath(droneId, searchId, path);
}

QList<QGeoCoordinate>* Persistence::retrieveDronePath(QUuid droneId, QUuid searchId)
{
    return dronesearchdao.dbRetrieveDronePath(droneId, searchId);
}

void Persistence::saveVideoSequence(QUuid droneId, QUuid searchId, VideoSequence *sequence)
{
    videosequencedao.dbSaveVideoSequence(droneId, searchId, sequence);
}

VideoSequence* Persistence::retrieveVideoSequence(QUuid droneId, QUuid searchId)
{
    return videosequencedao.dbRetrieveVideoSequence(droneId, searchId);
}

void Persistence::saveDetectionResult(QUuid droneId, QUuid searchId, DetectionResult *result)
{
    detectionresultdao.dbSaveDetectionResult(droneId, searchId, result);
}

QList<DetectionResult*>* Persistence::retrieveDetectionResults(QUuid droneId, QUuid searchId)
{
    return detectionresultdao.dbRetrieveDetectionResults(droneId, searchId);
}

QList<DetectionResult*>* Persistence::retrieveDetectionResults(QUuid searchId)
{
    return detectionresultdao.dbRetrieveDetectionResults(searchId);
}

void Persistence::initDatabase()
{
    bool dbNotCreatedYet = false;

    // Make sure the file exists
    QFileInfo checkFile(databaseLocation());
    if (!checkFile.exists() || !checkFile.isFile()) {
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

    if (dbNotCreatedYet) {
        createDatabase();
    }

}

QString Persistence::databaseLocation()
{
    QString folder = QStandardPaths::writableLocation(QStandardPaths::DataLocation);

    //create folder if not available
    QDir(QDir::root()).mkpath(folder);

    if (!folder.endsWith(QDir::separator()))
        folder.append(QDir::separator());

    QString name = "database.sqlite";

    return folder.append(name);
}

void Persistence::createDatabase()
{
    QFile sqlScheme(":/db/createTables.sql");
    if (sqlScheme.open(QIODevice::ReadOnly)) {
        QSqlQuery query(projectShaeDatabase);
        QStringList queryStrings = QTextStream(&sqlScheme).readAll().split(';');
        // Can't execute several queries at once, so split them
        // and execute them one by one.
        Q_FOREACH (QString queryString, queryStrings) {
            if (!query.exec(queryString))
                qDebug() << "Could not issue command: " << queryString;
        }
    } else {
        qDebug() << "Error opening file to create database";
    }
}

