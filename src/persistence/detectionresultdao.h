#ifndef DETECTIONRESULTDAO_H
#define DETECTIONRESULTDAO_H

#include <QtSql>
#include "models/detectionresult.h"

class DetectionResultDAO
{
public:
    DetectionResultDAO();
    DetectionResultDAO(QSqlDatabase* projectShaeDatabase);
    //
    DetectionResult dbSaveDetectionResult(QUuid droneId, QUuid searchId, DetectionResult result);
    QList<DetectionResult> dbRetrieveDetectionResults(QUuid droneId, QUuid searchId);
private:
    QSqlDatabase* projectShaeDatabase;
};

#endif // DETECTIONRESULTDAO_H
