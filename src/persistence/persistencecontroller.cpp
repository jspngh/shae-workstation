#include "persistencecontroller.h"

PersistenceController::PersistenceController(Mediator *mediator, QObject *parent)
    : QObject(parent),
      mediator(mediator)
{
    this->persistence = new Persistence(mediator, this);

    mediator->addSlot(this, SLOT(saveSearch(Search)), QString("saveSearch(Search)"));
}

void PersistenceController::saveSearch(Search s)
{
    persistence->saveSearch(s);
    foreach(DroneModule *dm, s.getDroneList())
    {
        Drone d = dm->getDrone();
        persistence->saveDrone(d);
        persistence->saveDronePath(d.getGuid(), s.getSearchID(), dm->getWaypoints());
    }
}
