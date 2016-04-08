#include "persistencecontroller.h"
#include <QDebug>

PersistenceController::PersistenceController(Mediator *mediator, QObject *parent)
    : QObject(parent),
      mediator(mediator)
{
    this->persistence = new Persistence(mediator, this);

    // Add save slots to mediator
    mediator->addSlot(this, SLOT(saveSearch(Search *)), QString("startSearch(Search*)"));
    mediator->addSlot(this, SLOT(saveDronePaths(Search *)), QString("pathCalculated(Search*)"));
    mediator->addSlot(this, SLOT(saveDroneStatus(DroneStatus)), QString("droneStatusReceived(DroneStatus)"));
    mediator->addSlot(this, SLOT(saveDetectionResult(DetectionResult)), QString("newDetection(DetectionResult))"));
    mediator->addSlot(this, SLOT(saveVideoSequence(VideoSequence)), QString("TODO"));
}

void PersistenceController::saveSearch(Search *s)
{
    persistence->saveSearch(*s);
    foreach(DroneModule *dm, s->getDroneList())
    {
        Drone d = dm->getDrone();
        persistence->saveDrone(d);
    }

}

void PersistenceController::saveDronePaths(Search *s)
{
    foreach(DroneModule *dm, s->getDroneList())
    {
        Drone d = dm->getDrone();
        persistence->saveDronePath(d.getGuid(), s->getSearchID(), *(dm->getWaypoints()));
    }
}

void PersistenceController::saveDroneStatus(DroneStatus ds)
{
    persistence->saveDroneStatus(s);
}

void PersistenceController::saveDetectionResult(DetectionResult dr)
{
    //TODO: add droneid and searchid
    persistence->saveDetectionResult(null, null, dr);
}

void PersistenceController::saveVideoSequence(VideoSequence vs)
{
    //TODO: add droneid and searchid
    persistence->saveVideoSequence(vs);
}


void PersistenceController::retrieveSearch(QUuid searchId)
{
    Search s = persistence->retrieveSearch(searchId);
    emit retrievedSearch(s);
}

void PersistenceController::retrieveDronePaths(QUuid droneId, QUuid searchId)
{
    QList<QGeoCoordinate> dps = persistence->retrieveDronePath(droneId, searchId);
    emit retrievedDronePaths(dps);
}

void PersistenceController::retrieveDroneStatus(QUuid droneId)
{
    DroneStatus ds = persistence->retrieveDroneStatus(droneId);
    emit retrievedDroneStatus(ds);
}

void PersistenceController::retrieveDroneStatus(QUuid droneId, QDateTime time)
{
    DroneStatus ds = persistence->retrieveDroneStatus(droneId, time);
    emit retrievedDroneStatus(ds);
}

void PersistenceController::retrieveDroneStatus(QUuid droneId, QDateTime begin, QDateTime end)
{
    QList<DroneStatus> dss = persistence->retrieveDroneStatus(droneId, begin, end);
    emit retrievedDroneStatus(dss);
}

void PersistenceController::retrieveDetectionResults(QUuid droneId, QUuid searchId)
{
    QList<DetectionResult> drs = persistence->retrieveDetectionResults(droneId, searchId);
    emit retrievedDetectionResults(drs);

}

void PersistenceController::retrieveVideoSequence(QUuid droneId, QUuid SearchId, QUuid videoId)
{
    VideoSequence vs = persistence->retrieveVideoSequence(droneId, searchId, videoId);
    emit retrievedVideoSequence(vs);
}


