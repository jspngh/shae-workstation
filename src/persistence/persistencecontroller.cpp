#include "persistencecontroller.h"
#include <QDebug>

PersistenceController::PersistenceController(Mediator *mediator, QObject *parent)
    : QObject(parent),
      mediator(mediator)
{
    this->persistence = new Persistence(mediator, this);

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
    persistence->saveVideoSequence(null, null, vs);
}


