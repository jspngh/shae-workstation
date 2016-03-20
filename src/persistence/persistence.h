#ifndef PERSISTENCE_H
#define PERSISTENCE_H

#include <QObject>
#include <QGeoCoordinate>
#include <QUuid>
#include "core/mediator.h"
#include "models/dronestatus.h"
#include "models/videosequence.h"
#include "models/detectionresult.h"
#include "models/search.h"
#include "models/drone.h"
#include "detectionresultdao.h"
#include "dronedao.h"
#include "dronestatusdao.h"
#include "searchdao.h"
#include "dronesearchdao.h"
#include "videosequencedao.h"

class Persistence : public QObject
{

    Q_OBJECT
public:
    Persistence(Mediator *mediator, QObject *parent = 0);
    ~Persistence();

signals:



    void onSaveSearch(Search search);
    void onRetrieveSearch(Search search);

    void onSaveDroneStatus(DroneStatus status);
    //compare with timestamp of workstation
    void onRetrieveDroneStatus(QList<DroneStatus> dronestatuses);
    //retrieve latest dronestatus
    void onRetrieveLatestDroneStatus(DroneStatus status);
    //retrieve dronestatus closest to time parameter
    void onRetrieveClosestDroneStatus(DroneStatus status);


    void onSaveDronePath(QList<QGeoCoordinate> path);
    void onRetrieveDronePath(QList<QGeoCoordinate> path);

    //void onSaveDrone(Drone drone);
    //void onRetrieveDrone(Drone drone);

    //will register a videosequence in the database (already saved in location)
    void onSaveVideoSequence(VideoSequence sequence);
    void onRetrieveVideoSequence(VideoSequence sequence);

    void onSaveDetectionResult(DetectionResult result);
    void onRetrieveDetectionResults(QList<DetectionResult> results);

public slots:
    void saveSearch(Search &search);
    void retrieveSearch(QUuid searchId);

    void saveDroneStatus(DroneStatus &droneStatus, QUuid droneId, QUuid searchId);
    //compare with timestamp of workstation
    void retrieveDroneStatus(QUuid droneId, QUuid searchId, QDateTime begin, QDateTime end);
    //retrieve latest dronestatus
    void retrieveDroneStatus(QUuid droneId, QUuid searchId);
    //retrieve dronestatus closest to time parameter
    void retrieveDroneStatus(QUuid droneId, QUuid searchId, QDateTime time);


    void saveDronePath(QUuid droneId, QUuid searchId, QList<QGeoCoordinate> path);
    void retrieveDronePath(QUuid droneId, QUuid searchId);

    //void saveDrone(Drone drone);
    //void retrieveDrone(QUuid droneId);

    //will register a videosequence in the database (already saved in location)
    void saveVideoSequence(QUuid droneId, QUuid searchId, VideoSequence &sequence);
    void retrieveVideoSequence(QUuid droneId, QUuid searchId, QUuid videoId);

    void saveDetectionResult(QUuid droneId, QUuid searchId, DetectionResult &result);
    void retrieveDetectionResults(QUuid droneId, QUuid searchId);

private:
    QSqlDatabase projectShaeDatabase;
    DetectionResultDAO detectionresultdao;
    DroneDAO dronedao;
    DroneSearchDAO  dronesearchdao;
    DroneStatusDAO dronestatusdao;
    SearchDAO searchdao;
    VideoSequenceDAO videosequencedao;
};

#endif // PERSISTENCE_H

