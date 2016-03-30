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

PathAlgorithm::PathAlgorithm(const PathAlgorithm& algo)
{
    start = algo.start;
    controller = algo.controller;
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
QGeoCoordinate PathAlgorithm::goDirectionBetween(QGeoCoordinate start, QGeoCoordinate coordinate1, QGeoCoordinate coordinate2, double distance, Direction direction)
{
    double rico = (coordinate2.latitude() - coordinate1.latitude())/(coordinate2.longitude() - coordinate1.longitude());
    QGeoCoordinate newpoint = QGeoCoordinate(start.latitude() + direction*rico*distance, start.longitude() + direction*distance);
    return newpoint;
}

void PathAlgorithm::onStartSearch(Search *s)
{
    qDebug() << "PathAlgorithm::onStartSearch(Search *s)";
    setWaypointsForDrones(s->getArea(), s->getDroneList());
    emit pathCalculated(s);
    qDebug() << "emit PathAlgorithm::pathCalculated(Search *s)";
}

