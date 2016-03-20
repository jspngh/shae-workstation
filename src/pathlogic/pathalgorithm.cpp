#include "pathalgorithm.h"

PathAlgorithm::PathAlgorithm(Mediator *mediator, QObject *p)
    : PathAlgorithm(QGeoCoordinate(0.0, 0.0), mediator)
{

}

PathAlgorithm::PathAlgorithm(QGeoCoordinate start, Mediator *mediator, QObject *p)
    : QObject(p),
      start(start),
      mediator(mediator)
{
    this->mediator->addSignal(this, SIGNAL(pathCalculated(Search*)), QString("pathCalculated(Search*)"));
    this->mediator->addSlot(this, SLOT(onStartSearch(Search*)), QString("startSearch(Search*)"));
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

PathAlgorithm::onStartSearch(Search *s)
{
    // TODO: for now, the drone width of the first drone is picked. This means there is no multidrone support.
    QList<QGeoCoordinate> waypoints = this->calculateWaypoints(s->getArea(), s->getDroneList().at(0).getVisionWidth());
    s->setWaypoints(waypoints);

    // signal that the path is calculated
    emit this->pathCalculated(s);
}
