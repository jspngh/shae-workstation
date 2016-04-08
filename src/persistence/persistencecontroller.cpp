#include "persistencecontroller.h"
#include <QDebug>

PersistenceController::PersistenceController(QObject *parent)
    : QObject(parent)
{
}

void PersistenceController::saveSearch(Search *s)
{
    persistence->saveSearch(*s);
    foreach(DroneModule *dm, s->getDroneList())
    {
        Drone *d = dm->getDrone();
        persistence->saveDrone(d);
    }

}

void PersistenceController::saveDronePaths(Search *s)
{
    foreach(DroneModule *dm, s->getDroneList())
    {
        Drone* d = dm->getDrone();
        persistence->saveDronePath(d->getGuid(), s->getSearchID(), dm->getWaypoints());
    }
}

void PersistenceController::saveDroneStatus(DroneStatus ds)
{
    persistence->saveDroneStatus(ds);
}

void PersistenceController::saveDetectionResult(DetectionResult dr)
{
    //TODO: add droneid and searchid
    persistence->saveDetectionResult(0, 0, dr);
}

void PersistenceController::saveVideoSequence(VideoSequence vs)
{
    //TODO: add droneid and searchid
    persistence->saveVideoSequence(0, 0, vs);
}


Search PersistenceController::retrieveSearch(QUuid searchId)
{
    return persistence->retrieveSearch(searchId);
}

QList<QGeoCoordinate> PersistenceController::retrieveDronePaths(QUuid droneId, QUuid searchId)
{
    return persistence->retrieveDronePath(droneId, searchId);
}

DroneStatus PersistenceController::retrieveDroneStatus(QUuid droneId)
{
    return persistence->retrieveDroneStatus(droneId);
}

DroneStatus PersistenceController::retrieveDroneStatus(QUuid droneId, QDateTime time)
{
    return persistence->retrieveDroneStatus(droneId, time);
}

QList<DroneStatus> PersistenceController::retrieveDroneStatus(QUuid droneId, QDateTime begin, QDateTime end)
{
    return persistence->retrieveDroneStatus(droneId, begin, end);
}

QList<DetectionResult> PersistenceController::retrieveDetectionResults(QUuid droneId, QUuid searchId)
{
    return persistence->retrieveDetectionResults(droneId, searchId);

}

VideoSequence PersistenceController::retrieveVideoSequence(QUuid droneId, QUuid searchId)
{
    return persistence->retrieveVideoSequence(droneId, searchId);
}


void PersistenceController::setMediator(Mediator *mediator)
{
    this->persistence = new Persistence(mediator, this);
    qDebug() << "adding PersistenceController signal/slots";
    // Add save slots to mediator
    mediator->addSlot(this, SLOT(saveSearch(Search *)), QString("startSearch(Search*)"));
    mediator->addSlot(this, SLOT(saveDronePaths(Search *)), QString("pathCalculated(Search*)"));
    mediator->addSlot(this, SLOT(saveDroneStatus(DroneStatus)), QString("droneStatusReceived(DroneStatus)"));
    mediator->addSlot(this, SLOT(saveDetectionResult(DetectionResult)), QString("newDetection(DetectionResult))"));
    mediator->addSlot(this, SLOT(saveVideoSequence(VideoSequence)), QString("TODO"));
}

