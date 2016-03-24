#include "pathalgorithm.h"
#include "core/controller.h"

PathAlgorithm::PathAlgorithm(QObject *p)
    : PathAlgorithm(QGeoCoordinate(0.0, 0.0))
{

}

PathAlgorithm::PathAlgorithm(QGeoCoordinate start, QObject *p)
    : QObject(p),
      start(start)
{

}

PathAlgorithm::~PathAlgorithm()
{

}

void PathAlgorithm::setController(Controller *value)
{
    controller = value;
    controller->getMediator()->addSignal(this, (char*) SIGNAL(pathCalculated(Search *)), QString("pathCalculated(Search*)"));
    controller->getMediator()->addSlot(this, (char*) SLOT(onStartSearch(Search *)), QString("startSearch(Search*)"));
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
    qDebug() << "PathAlgorithm::onStartSearch(Search *s)";
    setWaypointsForDrones(s->getArea(), s->getDroneList());
    emit pathCalculated(s);
    qDebug() << "emit PathAlgorithm::pathCalculated(Search *s)";
}

