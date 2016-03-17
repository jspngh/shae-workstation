#ifndef PERSISTENCE_H
#define PERSISTENCE_H
#include <QUuid>
#include "core/models/dronestatus.h"
#include "core/models/videosequence.h"
#include "core/models/detectionresult.h"
#include "core/models/search.h"
#include <QGeoCoordinate>

class Persistence
{
public:
    Persistence();

    Search saveSearch(Search &search);
    Search retrieveSearch(QUuid searchId);

    DroneStatus saveDroneStatus(DroneStatus &droneStatus, QUuid droneId, QUuid searchId);
    //compare with timestamp of workstation
    std::list<DroneStatus> retrieveDroneStatus(QUuid droneId, QUuid searchId, QTime begin, QTime end);
    //retrieve latest dronestatus
    DroneStatus retrieveDroneStatus(QUuid droneId, QUuid searchId);
    //retrieve dronestatus closest to time parameter
    DroneStatus retrieveDroneStatus(QUuid droneId, QUuid searchId, QTime time);


    std::list<QGeoCoordinate> saveDronePath(QUuid droneId, QUuid searchId, std::list<QGeoCoordinate> path);
    std::list<QGeoCoordinate> retrieveDronePath(QUuid droneId, QUuid searchId);

    //will register a videosequence in the database (already saved in location)
    VideoSequence saveVideoSequence(QUuid droneId, QUuid searchId, VideoSequence &sequence);
    VideoSequence retrieveVideoSequence(QUuid droneId, QUuid searchId, QUuid videoId);

    DetectionResult saveDetectionResult(QUuid droneId, QUuid searchId, DetectionResult &result);
    std::list<DetectionResult> retrieveDetectionResults(QUuid droneId, QUuid searchId);
};

#endif // PERSISTENCE_H
