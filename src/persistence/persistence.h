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
#include "detectionresultwriter.h"

/*!
 * \brief The Persistence class
 * \ingroup Persistence
 */
class Persistence : public QObject
{

    Q_OBJECT
public:

    Persistence();
    /**
     * \brief The basic constructor for Persistence needs the mediator as input.
     */
    Persistence(Mediator *mediator, QObject *parent = 0);
    /**
     * \brief The basic destructor for Persistence.
     */
    ~Persistence();

    /**
     * \brief Gets the a search out of the database by calling a method in searchdao, the input is the uuid of the search.
     */
    Search *retrieveSearch(QUuid searchId);
    /**
     * \brief Gets the dronestatuses out of the database by calling a method in dronestatusdao.
     * The input is the uuid of the drone, the begin and end datetime of the dronestatuses.
     * This method will return a list of all the dronestatus of the specified drone between begin and end.
     */
    QList<DroneStatus *> *retrieveDroneStatus(QUuid droneId, QDateTime begin, QDateTime end);
    /**
     * \brief Gets the dronestatuses out of the database by calling a method in dronestatusdao.
     * The input is the uuid of the drone.
     * This method will return the latest dronestatus of the specified drone.
     */
    DroneStatus *retrieveDroneStatus(QUuid droneId);
    /**
     * \brief Gets the dronestatuses out of the database by calling a method in dronestatusdao.
     * The input is the uuid of the drone and time which is a reference time.
     * This method will return the latest dronestatus compared to the reference time.
     */
    DroneStatus *retrieveDroneStatus(QUuid droneId, QDateTime time);
    /**
     * \brief Gets the dronepath out of the dronesearchdao for a specified drone and search.
     * The input is the uuid of the drone and the uuid of the search.
     * This method will return a list ogeocoordinates of the path of the drone.
     */
    QList<QGeoCoordinate> *retrieveDronePath(QUuid droneId, QUuid searchId);
    /**
     * \brief Gets the drone out of the database by calling a method in dronedao.
     * The input is the uuid of the drone.
     * This method will return the drone.
     */
    Drone *retrieveDrone(QUuid droneId);
    /**
     * \brief Gets al the droneids out of the database by calling a method in dronesearchdao.
     * The input is the uuid of the search.
     * This method will return a list of all the droneids of the search.
     */
    QList<QUuid> *retrieveDroneIds(QUuid searchId);
    /**
     * \brief Gets the videosequence out of the database by calling a method in videosequencedao.
     * The input is the uuid of the drone and the uuid of the search.
     * This method will return a videosequence for the specified drone and search.
     */
    VideoSequence *retrieveVideoSequence(QUuid droneId, QUuid searchId);
    /**
     * \brief Gets the detection results out of the database by calling a method in detectionresultdao.
     * The input is the uuid of the drone and the uuid of the search.
     * This method will return a list of all the detectionresults for the specified drone and search.
     */
    QList<DetectionResult *> *retrieveDetectionResults(QUuid droneId, QUuid searchId);
    /**
     * \brief Gets the detection results out of the database by calling a method in detectionresultdao.
     * The input is the uuid of the drone.
     * This method will return a list of all the detectionresults for the specified drone.
     */
    QList<DetectionResult *> *retrieveDetectionResults(QUuid searchId);

    //! \brief Save a search in the database by calling a method on the correct DAO.
    void saveSearch(Search *search);
    //! \brief Save a dronestatus in the database by calling a method on the correct DAO.
    void saveDroneStatus(DroneStatus *droneStatus);
    //! \brief Save a drone path in the database by calling a method on the correct DAO.
    void saveDronePath(QUuid droneId, QUuid searchId, QList<QGeoCoordinate> *path);
    //! \brief Save a drone in the database by calling a method on the correct DAO.
    void saveDrone(Drone *drone);
    //! \brief This will print the detectionresults for a search to a file in TXT format.
    void printDetectionResultTXT(QUuid searchId, QString fileName);
    //! \brief This will print the detectionresults for a search to a file in XML format.
    void printDetectionResultXML(QUuid searchId, QString fileName);
    //! \brief Save a videosequence in the database by calling a method on the correct DAO.
    void saveVideoSequence(QUuid droneId, QUuid searchId, VideoSequence *sequence);
    //! \brief Save a detectionresult in the database by calling a method on the correct DAO.
    void saveDetectionResult(QUuid droneId, QUuid searchId, DetectionResult *result);


public slots:

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

