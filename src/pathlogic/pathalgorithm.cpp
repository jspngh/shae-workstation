#include "pathalgorithm.h"
#include "core/controller.h"

PathAlgorithm::PathAlgorithm(Controller *controller, QObject *p)
    : PathAlgorithm(controller, QGeoCoordinate(0.0, 0.0))
{

}

PathAlgorithm::PathAlgorithm(Controller *c, QGeoCoordinate start, QObject *p)
    : QObject(p),
      start(start),
      controller(c)
{
    controller->getMediator()->addSignal(this, SIGNAL(pathCalculated(Search*)), QString("pathCalculated(Search*)"));
    controller->getMediator()->addSlot(this, SLOT(onStartSearch(Search*)), QString("startSearch(Search*)"));
}

PathAlgorithm::~PathAlgorithm()
{

}

QGeoCoordinate PathAlgorithm::goDirection(QGeoCoordinate start, Direction direction, double distance)
{
    switch (direction) {
    case NORTH:
        return   QGeoCoordinate(start.latitude() + distance, start.longitude());
        break;
    case SOUTH:
        return   QGeoCoordinate(start.latitude() - distance, start.longitude());
        break;
    case WEST:
        return   QGeoCoordinate(start.latitude(), start.longitude() - distance);
        break;
    case EAST:
        return   QGeoCoordinate(start.latitude(), start.longitude() + distance);
        break;
    default:
        return start ;
        break;
    }

}

void PathAlgorithm::onStartSearch(Search *s)
{
    // TODO: for now, the drone width of the first drone is picked. This means there is no multidrone support.
   // QList<QGeoCoordinate> waypoints = calculateWaypoints(s->getArea(), (s->getDroneList()->at(0)).getVisionWidth());

    s->setWaypoints(0);

    // signal that the path is calculated
    emit pathCalculated(s);
}
