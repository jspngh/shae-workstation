#include "detectionresultdao.h"

DetectionResultDAO::DetectionResultDAO()
{

}

DetectionResultDAO::DetectionResultDAO(QSqlDatabase* projectShaeDatabase){
    this->projectShaeDatabase = projectShaeDatabase;
}

DetectionResult DetectionResultDAO::dbSaveDetectionResult(QUuid droneId, QUuid searchId, DetectionResult result)
{
    // todo check if args are ok
    QSqlQuery query;
    query.prepare("INSERT INTO detectionresults (videoID, searchID, droneID, latitude, longitude, score) "
                  "VALUES (:videoID, :searchID, :droneID, :latitude, :longitude, :score)");
    query.bindValue(":videoID", result.getVideoSequence().getVideoID());
    query.bindValue(":searchID", searchId);
    query.bindValue(":droneID", droneId);
    QGeoCoordinate location = result.getLocation();
    query.bindValue(":latitude", location.latitude());
    query.bindValue(":longitude", location.longitude());
    query.bindValue(":score", result.getScore());
    if(query.exec())
    {
       qDebug() << "insert succes";
    }
    else
    {
       qDebug() << "addDetectionResult error:  "
                << query.lastError();
    }
    return result;
}

QList<DetectionResult> DetectionResultDAO::dbRetrieveDetectionResults(QUuid droneId, QUuid searchId)
{
    QSqlQuery query;
    QList<DetectionResult> returnList = QList<DetectionResult>();
    query.prepare("SELECT videoID, latitude, longitude, score FROM detectionresults WHERE searchID = (:searchID) and droneID = (:droneID)");
    query.bindValue(":searchID", searchId);
    query.bindValue(":droneID", droneId);
    if(query.exec())
    {
        while (query.next()) {
            DetectionResult output = DetectionResult(QGeoCoordinate(query.value(1).toDouble(),query.value(2).toDouble()), query.value(3).toDouble(), VideoSequence(QUuid(query.value(0).toString())));
            returnList.append(output);
        }
        for(DetectionResult dr : returnList){
            QSqlQuery queryVideoSequence;
            queryVideoSequence.prepare("SELECT start, end, frameCount, path FROM videosequences WHERE videoID = (:videoID)");
            queryVideoSequence.bindValue(":videoID", dr.getVideoSequence().getVideoID().toString());
            if(queryVideoSequence.exec())
            {
                if(queryVideoSequence.next())
                {
                    dr.getVideoSequence().setVariables(queryVideoSequence.value(0).toTime(),
                                                       queryVideoSequence.value(1).toTime(),
                                                       queryVideoSequence.value(2).toInt(),
                                                       queryVideoSequence.value(3).toString());
                }
            }
            else
            {
                qDebug() << "getVideoSequence in getdetectionresult error:  "
                         << query.lastError();
            }
        }
    }
    else
    {
       qDebug() << "getDetectionResult error:  "
                << query.lastError();
    }
    return returnList;
}
