#ifndef DETECTIONRESULTDAO_H
#define DETECTIONRESULTDAO_H

#include <QtSql>
#include "models/detectionresult.h"
#include "generaldao.h"

/**
 * \brief The DetectionResultDAO class is responsible for loading and saving
 * detectionresult models into the database.
 */

class DetectionResultDAO : GeneralDAO
{
public:
    /**
     * \brief The basic constructor for a DetectionResultDAO needs a database as input.
     */
    DetectionResultDAO();
    DetectionResultDAO(QSqlDatabase* projectShaeDatabase);
    //
    /**
     * \brief dbSaveDetectionResult saves a detection result into the database.
     * Its inputs are a droneid, searchid and detectionresult object.
     * Both ids are for referencing to tables in the database while the object is
     * the one that needs to be stored.
     */
    DetectionResult dbSaveDetectionResult(QUuid droneId, QUuid searchId, DetectionResult result);
    /**
     * \brief dbRetrieveDetectionResult Retrieves al the detection results for a
     * certain drone and search.
     */
    QList<DetectionResult> dbRetrieveDetectionResults(QUuid droneId, QUuid searchId);
private:
    QSqlDatabase* projectShaeDatabase;
};

#endif // DETECTIONRESULTDAO_H
