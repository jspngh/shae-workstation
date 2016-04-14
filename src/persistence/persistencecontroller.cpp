#include "persistencecontroller.h"
#include <QDebug>

PersistenceController::PersistenceController(QObject *parent)
    : QObject(parent)
{

}

void PersistenceController::setMediator(Mediator *mediator)
{
    this->persistence = new Persistence(mediator, this);
    qDebug() << "adding PersistenceController signal/slots";
    // Add save slots to mediator
    mediator->addSlot(this, SLOT(saveSearch(Search *)), QString("startSearch(Search*)"));
    mediator->addSlot(this, SLOT(saveDronePaths(Search *)), QString("pathCalculated(Search*)"));
    mediator->addSlot(this, SLOT(saveDroneStatus(DroneStatus)), QString("droneStatusReceived(DroneStatus)"));
    mediator->addSlot(this, SLOT(saveDroneStatus(DroneStatus)), QString("droneHeartBeatReceived(DroneStatus)"));
    mediator->addSlot(this, SLOT(saveDetectionResult(QUuid, DetectionResult)), QString("newDetection(QUuid, DetectionResult)"));
    mediator->addSlot(this, SLOT(saveVideoSequence(QUuid, VideoSequence)), QString("streamStarted(QUuid, VideoSequence)"));
}

void PersistenceController::saveSearch(Search *s)
{
    persistence->saveSearch(*s);
    foreach(DroneModule *dm, s->getDroneList())
    {
        Drone *d = dm->getDrone();
        persistence->saveDrone(d);
    }

    this->currentSearch = s;
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

void PersistenceController::saveDetectionResult(QUuid droneId, DetectionResult dr)
{
    persistence->saveDetectionResult(droneId, currentSearch->getSearchID(), dr);
}

void PersistenceController::saveVideoSequence(QUuid droneId, VideoSequence vs)
{
    persistence->saveVideoSequence(droneId, currentSearch->getSearchID(), vs);
}


Search PersistenceController::retrieveSearch(QUuid searchId)
{
    return persistence->retrieveSearch(searchId);
}

QList<QGeoCoordinate> PersistenceController::retrieveDronePaths(QUuid droneId, QUuid searchId)
{
    return persistence->retrieveDronePath(droneId, searchId);
}

Drone PersistenceController::retrieveDrone(QUuid droneId)
{
    return persistence->retrieveDrone(droneId);
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

