#include "persistencecontroller.h"
#include <QDebug>

PersistenceController::PersistenceController(QObject *parent)
    : QObject(parent)
{

}

void PersistenceController::setMediator(Mediator *mediator)
{
    this->persistence = new Persistence(mediator, this);
    this->detectionresultwriter = new DetectionResultWriter();

    qDebug() << "adding PersistenceController signal/slots";
    // Add save slots to mediator
    mediator->addSlot(this, SLOT(saveSearch(Search *)), QString("startSearch(Search*)"));
    mediator->addSlot(this, SLOT(saveDronePaths(Search *)), QString("pathCalculated(Search*)"));
    mediator->addSlot(this, SLOT(saveDroneStatus(DroneStatus*)), QString("droneStatusReceived(DroneStatus*)"));
    mediator->addSlot(this, SLOT(saveDroneStatus(DroneStatus*)), QString("droneHeartBeatReceived(DroneStatus*)"));
    mediator->addSlot(this, SLOT(saveDetectionResult(QUuid, DetectionResult)), QString("newDetection(QUuid, DetectionResult)"));
    mediator->addSlot(this, SLOT(saveVideoSequence(QUuid, VideoSequence)), QString("streamStarted(QUuid, VideoSequence)"));
    mediator->addSlot(this, SLOT(printDetectionResult(QUuid, QString)), QString("printDetectionResult(QUuid, QString)"));
}

void PersistenceController::saveSearch(Search *s)
{
    persistence->saveSearch(s);
    foreach(DroneModule *dm, s->getDroneList())
    {
        Drone *d = dm->getDrone();
        persistence->saveDrone(d);
    }

    this->currentSearch = s;
}

void PersistenceController::saveDronePaths(Search *s)
{
    foreach (DroneModule *dm, s->getDroneList()) {
        Drone *d = dm->getDrone();
        persistence->saveDronePath(d->getGuid(), s->getSearchID(), dm->getWaypoints());
    }
}

void PersistenceController::saveDroneStatus(DroneStatus *ds)
{
    persistence->saveDroneStatus(ds);
}

void PersistenceController::saveDetectionResult(QUuid droneId, DetectionResult *dr)
{
    persistence->saveDetectionResult(droneId, currentSearch->getSearchID(), dr);
}

void PersistenceController::saveVideoSequence(QUuid droneId, VideoSequence *vs)
{
    persistence->saveVideoSequence(droneId, currentSearch->getSearchID(), vs);
}


Search* PersistenceController::retrieveSearch(QUuid searchId)
{
    Search *s = persistence->retrieveSearch(searchId);

    QList<QUuid>* droneIds = persistence->retrieveDroneIds(searchId);
    QList<DroneModule*> droneModules = QList<DroneModule*>();
    foreach (QUuid droneId, *droneIds)
    {
        DroneModule *dm = new DroneModule();
        Drone *drone = persistence->retrieveDrone(droneId);
        dm->setDrone(drone);
        droneModules.append(dm);
    }
    s->setDroneList(droneModules);
    return s;
}

QList<QGeoCoordinate>* PersistenceController::retrieveDronePaths(QUuid droneId, QUuid searchId)
{
    return persistence->retrieveDronePath(droneId, searchId);
}

Drone* PersistenceController::retrieveDrone(QUuid droneId)
{
    return persistence->retrieveDrone(droneId);
}

DroneStatus* PersistenceController::retrieveDroneStatus(QUuid droneId)
{
    return persistence->retrieveDroneStatus(droneId);
}

DroneStatus* PersistenceController::retrieveDroneStatus(QUuid droneId, QDateTime time)
{
    return persistence->retrieveDroneStatus(droneId, time);
}

QList<DroneStatus*>* PersistenceController::retrieveDroneStatus(QUuid droneId, QDateTime begin, QDateTime end)
{
    return persistence->retrieveDroneStatus(droneId, begin, end);
}

QList<DetectionResult*>* PersistenceController::retrieveDetectionResults(QUuid droneId, QUuid searchId)
{
    return persistence->retrieveDetectionResults(droneId, searchId);

}

void PersistenceController::printDetectionResult(QUuid searchId, QString fileName)
{
    QList<DetectionResult*>* results = persistence->retrieveDetectionResults(searchId);
    detectionresultwriter->writeDetectionResultToFile(fileName, results);
}

VideoSequence* PersistenceController::retrieveVideoSequence(QUuid droneId, QUuid searchId)
{
    return persistence->retrieveVideoSequence(droneId, searchId);
}

