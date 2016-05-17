#ifndef PERSISTENCECONTROLLER_H
#define PERSISTENCECONTROLLER_H

#include <QObject>
#include "core/mediator.h"
#include "persistence.h"
#include "detectionresultwriter.h"

/*!
 * \brief The PersistenceController class
 * \ingroup Persistence
 */
class PersistenceController : public QObject
{
    Q_OBJECT
public:
    //! \brief Basic constructor of persistencecontroller.
    explicit PersistenceController(QObject *parent = 0);
    //! \brief Basic deconstructor of persistencecontroller.
    ~PersistenceController() {}

    //! \brief Set the mediator.
    void setMediator(Mediator *mediator);

    //! \brief This will print the detectionresults for a search to a file.
    Search *retrieveSearch(QUuid searchId);
    //! \brief Retrieve a drone's path for a search.
    QList<QGeoCoordinate> *retrieveDronePaths(QUuid droneId, QUuid searchId);
    //! \brief Retrieve a drone.
    Drone *retrieveDrone(QUuid droneId);
    //! \brief Retrieve the latests dronestatus.
    DroneStatus *retrieveDroneStatus(QUuid droneId);
    //! \brief Retrieve the latest dronestatus to a timestamp.
    DroneStatus *retrieveDroneStatus(QUuid droneId, QDateTime time);
    //! \brief Retrieve the dronestatuses between two timestamps.
    QList<DroneStatus *> *retrieveDroneStatus(QUuid droneId, QDateTime begin, QDateTime end);
    //! \brief Retrieve the detection results for a drone and search.
    QList<DetectionResult *> *retrieveDetectionResults(QUuid droneId, QUuid searchId);
    //! \brief Retrieve videosequence for a drone and search.
    VideoSequence *retrieveVideoSequence(QUuid droneId, QUuid SearchId);
public slots:
    //! \brief Slot to save a search.
    void saveSearch(Search *s);
    //! \brief Slot to save a dronepath.
    void saveDronePaths(Search *s);
    //! \brief Slot to print an XML file with detectionresults.
    void printDetectionResultXML(QString filePath);
    //! \brief Slot to print and TXT file with detectionresults.
    void printDetectionResultTXT(QString filePath);
    //! \brief Slot to save a dronestatus.
    void saveDroneStatus(DroneStatus *ds);
    //! \brief Slot to save a detectionresult.
    void saveDetectionResult(QUuid droneId, DetectionResult *dr);
    //! \brief Slot to save a videosequence.
    void saveVideoSequence(QUuid droneId, VideoSequence *vs);

private:
    Mediator *mediator;
    Persistence *persistence;
    Search *currentSearch;
    DetectionResultWriter *detectionresultwriter;
};

#endif // PERSISTENCECONTROLLER_H
