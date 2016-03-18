#ifndef PERSISTENCE_H
#define PERSISTENCE_H

#include <QObject>
#include <QGeoCoordinate>
#include <QUuid>
#include "models/dronestatus.h"
#include "models/videosequence.h"
#include "models/detectionresult.h"
#include "models/search.h"

class Persistence : public QObject
{
public:
    Persistence(QObject *parent = 0);

    Search saveSearch(Search &search);
    Search retrieveSearch(QUuid searchId);

    DroneStatus saveDroneStatus(DroneStatus &droneStatus, QUuid droneId, QUuid searchId);
    //compare with timestamp of workstation
    QList<DroneStatus> retrieveDroneStatus(QUuid droneId, QUuid searchId, QTime begin, QTime end);
    //retrieve latest dronestatus
    DroneStatus retrieveDroneStatus(QUuid droneId, QUuid searchId);
    //retrieve dronestatus closest to time parameter
    DroneStatus retrieveDroneStatus(QUuid droneId, QUuid searchId, QTime time);


    QList<QGeoCoordinate> saveDronePath(QUuid droneId, QUuid searchId, QList<QGeoCoordinate> path);
    QList<QGeoCoordinate> retrieveDronePath(QUuid droneId, QUuid searchId);

    //will register a videosequence in the database (already saved in location)
    VideoSequence saveVideoSequence(QUuid droneId, QUuid searchId, VideoSequence &sequence);
    VideoSequence retrieveVideoSequence(QUuid droneId, QUuid searchId, QUuid videoId);

    DetectionResult saveDetectionResult(QUuid droneId, QUuid searchId, DetectionResult &result);
    QList<DetectionResult> retrieveDetectionResults(QUuid droneId, QUuid searchId);
};

#endif // PERSISTENCE_H

