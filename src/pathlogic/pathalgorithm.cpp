#include "pathalgorithm.h"
#include <QDebug>

PathAlgorithm::PathAlgorithm(QObject *p)
    : PathAlgorithm(QGeoCoordinate(0.0, 0.0), p)
{

}

PathAlgorithm::PathAlgorithm(QGeoCoordinate start, QObject *p)
    : QObject(p),
      start(start)
{

}

PathAlgorithm::PathAlgorithm(const PathAlgorithm &algo)
{
    start = algo.start;
    mediator = algo.mediator;
}

PathAlgorithm::~PathAlgorithm()
{

}

void PathAlgorithm::setMediator(Mediator *mediator)
{
    qDebug() << "adding PathAlgorithm signal/slots";
    this->mediator = mediator;
    mediator->addSignal(this, SIGNAL(pathCalculated(Search *)), QString("pathCalculated(Search*)"));
    mediator->addSlot(this, SLOT(onStartSearch(Search *)), QString("startSearch(Search*)"));
}

QGeoCoordinate PathAlgorithm::goDirection(QGeoCoordinate start, Direction direction, double distance)
{
    switch (direction) {
    case WEST:
        return QGeoCoordinate(start.latitude(), start.longitude() - distance);
        break;
    case EAST:
        return QGeoCoordinate(start.latitude(), start.longitude() + distance);
        break;
    default:
        return start;
        break;
    }

}
QGeoCoordinate PathAlgorithm::goDirectionBetween(QGeoCoordinate start, QGeoCoordinate coordinate1, QGeoCoordinate coordinate2, double distance, Direction direction)
{
    double rico = (coordinate2.latitude() - coordinate1.latitude()) / (coordinate2.longitude() - coordinate1.longitude());
    QGeoCoordinate newpoint = QGeoCoordinate(start.latitude() + direction * rico * distance, start.longitude() + direction * distance);
    return newpoint;
}

void PathAlgorithm::onStartSearch(Search *s)
{
    qDebug() << "PathAlgorithm::onStartSearch(Search *s)";
    setWaypointsForDrones(s->getArea(), s->getDroneList());
    emit pathCalculated(s);
    qDebug() << "emit PathAlgorithm::pathCalculated(Search *s)";
}

