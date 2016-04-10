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
#include "detectionresultwriter.h"
#include "dronedao.h"
#include "dronestatusdao.h"
#include "searchdao.h"
#include "dronesearchdao.h"
#include "videosequencedao.h"

class Persistence : public QObject
{

    Q_OBJECT
public:
    Persistence();
    Persistence(Mediator *mediator, QObject *parent = 0);
    ~Persistence();

    Search retrieveSearch(QUuid searchId);
    //compare with timestamp of workstation
    QList<DroneStatus> retrieveDroneStatus(QUuid droneId, QDateTime begin, QDateTime end);
    //retrieve latest dronestatus
    DroneStatus retrieveDroneStatus(QUuid droneId);
    //retrieve dronestatus closest to time parameter
    DroneStatus retrieveDroneStatus(QUuid droneId, QDateTime time);
    QList<QGeoCoordinate> retrieveDronePath(QUuid droneId, QUuid searchId);
    Drone retrieveDrone(QUuid droneId);
    VideoSequence retrieveVideoSequence(QUuid droneId, QUuid searchId);
    QList<DetectionResult> retrieveDetectionResults(QUuid droneId, QUuid searchId);
    QList<DetectionResult> retrieveDetectionResults(QUuid searchId);

public slots:

    void saveSearch(Search search);
    void saveDroneStatus(DroneStatus droneStatus);
    void saveDronePath(QUuid droneId, QUuid searchId, QList<QGeoCoordinate> path);
    void saveDrone(Drone drone);
    //will register a videosequence in the database (already saved in location)
    void saveVideoSequence(QUuid droneId, QUuid searchId, VideoSequence sequence);
    void saveDetectionResult(QUuid droneId, QUuid searchId, DetectionResult result);
    void printDetectionResult(QUuid searchId, QString fileName);


private:
    QSqlDatabase projectShaeDatabase;
    DetectionResultDAO detectionresultdao;
    DroneDAO dronedao;
    DroneSearchDAO  dronesearchdao;
    DroneStatusDAO dronestatusdao;
    SearchDAO searchdao;
    VideoSequenceDAO videosequencedao;
    DetectionResultWriter detectionresultwriter;

    //! \brief Initializes the database (sets the projectShaeDatabase-property).
    void initDatabase();
    //! \brief Returns the path to the database file.
    QString databaseLocation();
    //!  \brief Create the database.
    void createDatabase();
};

#endif // PERSISTENCE_H

