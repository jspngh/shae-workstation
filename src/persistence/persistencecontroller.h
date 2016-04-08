#ifndef PERSISTENCECONTROLLER_H
#define PERSISTENCECONTROLLER_H

#include <QObject>
#include "core/mediator.h"
#include "persistence.h"

class PersistenceController : public QObject
{
    Q_OBJECT
public:
    explicit PersistenceController(Mediator *mediator, QObject *parent = 0);
    ~PersistenceController(){}

signals:
    void retrievedSearch(Search s);
    void retrievedDronePaths(QList<QGeoCoordinate> cs);
    void retrievedDroneStatus(QList<DroneStatus> dss);
    void retrievedDroneStatus(DroneStatus ds);
    void retrievedDetectionResults(QList<DetectionResult> drs);
    void retrievedVideoSequence(VideoSequence vs);

public slots:
    void saveSearch(Search *s);
    void saveDronePaths(Search *s);
    void saveDroneStatus(DroneStatus ds);
    void saveDetectionResult(DetectionResult dr);
    void saveVideoSequence(VideoSequence vs);

    void retrieveSearch(QUuid searchId);
    void retrieveDronePaths(QUuid droneId, QUuid searchId);
    void retrieveDroneStatus(QUuid droneId);
    void retrieveDroneStatus(QUuid droneId, QDateTime time);
    void retrieveDroneStatus(QUuid droneId, QDateTime begin, QDateTime end);
    void retrieveDetectionResults(QUuid droneId, QUuid searchId);
    void retrieveVideoSequence(QUuid droneId, QUuid SearchId, QUuid videoId);

private:
    Mediator *mediator;
    Persistence *persistence;
};

#endif // PERSISTENCECONTROLLER_H
