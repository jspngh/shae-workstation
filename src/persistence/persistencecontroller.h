#ifndef PERSISTENCECONTROLLER_H
#define PERSISTENCECONTROLLER_H

#include <QObject>
#include "core/mediator.h"
#include "persistence.h"

class PersistenceController : public QObject
{
    Q_OBJECT
public:
    explicit PersistenceController(QObject *parent = 0);
    ~PersistenceController() {}

    // Setter
    void setMediator(Mediator *mediator);

    Search retrieveSearch(QUuid searchId);
    QList<QGeoCoordinate> retrieveDronePaths(QUuid droneId, QUuid searchId);
    Drone retrieveDrone(QUuid droneId);
    DroneStatus retrieveDroneStatus(QUuid droneId);
    DroneStatus retrieveDroneStatus(QUuid droneId, QDateTime time);
    QList<DroneStatus> retrieveDroneStatus(QUuid droneId, QDateTime begin, QDateTime end);
    QList<DetectionResult> retrieveDetectionResults(QUuid droneId, QUuid searchId);
    VideoSequence retrieveVideoSequence(QUuid droneId, QUuid SearchId);
public slots:
    void saveSearch(Search *s);
    void saveDronePaths(Search *s);
    void saveDroneStatus(DroneStatus ds);
    void saveDetectionResult(QUuid droneId, DetectionResult dr);
    void saveVideoSequence(QUuid droneId, VideoSequence vs);

private:
    Mediator *mediator;
    Persistence *persistence;
    Search *currentSearch;
};

#endif // PERSISTENCECONTROLLER_H
