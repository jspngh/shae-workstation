#include "detectionresultdao.h"

DetectionResultDAO::DetectionResultDAO()
{

}

DetectionResultDAO::DetectionResultDAO(QSqlDatabase *projectShaeDatabase)
{
    this->projectShaeDatabase = projectShaeDatabase;
}

DetectionResult *DetectionResultDAO::dbSaveDetectionResult(QUuid droneId, QUuid searchId, DetectionResult *result)
{
    // todo check if args are ok
    QSqlQuery query;
    query.prepare("INSERT INTO detectionresults (searchID, droneID, latitude, longitude, score) "
                  "VALUES (:searchID, :droneID, :latitude, :longitude, :score)");
    query.bindValue(":searchID", searchId);
    query.bindValue(":droneID", droneId);
    QGeoCoordinate location = result->getLocation();
    query.bindValue(":latitude", location.latitude());
    query.bindValue(":longitude", location.longitude());
    query.bindValue(":score", result->getScore());
    if (query.exec()) {
    } else {
        qDebug() << "addDetectionResult error:  "
                 << query.lastError();
    }
    return result;
}

QList<DetectionResult *> *DetectionResultDAO::dbRetrieveDetectionResults(QUuid droneId, QUuid searchId)
{
    QSqlQuery query;
    QList<DetectionResult *> *returnList = new QList<DetectionResult *>();
    query.prepare("SELECT latitude, longitude, score FROM detectionresults WHERE searchID = (:searchID) and droneID = (:droneID)");
    query.bindValue(":searchID", searchId);
    query.bindValue(":droneID", droneId);
    if (query.exec()) {
        while (query.next()) {
            DetectionResult *output = new DetectionResult(QGeoCoordinate(query.value(0).toDouble(), query.value(1).toDouble()), query.value(2).toDouble());
            returnList->append(output);
        }
    } else {
        qDebug() << "getDetectionResult error:  "
                 << query.lastError();
    }
    return returnList;
}

QList<DetectionResult *> *DetectionResultDAO::dbRetrieveDetectionResults(QUuid searchId)
{
    QSqlQuery query;
    QList<DetectionResult *> *returnList = new QList<DetectionResult *>();
    query.prepare("SELECT latitude, longitude, score FROM detectionresults WHERE searchID = (:searchID)");
    query.bindValue(":searchID", searchId);
    if (query.exec()) {
        while (query.next()) {
            DetectionResult *output = new DetectionResult(QGeoCoordinate(query.value(0).toDouble(), query.value(1).toDouble()), query.value(2).toDouble());
            returnList->append(output);
        }
    } else {
        qDebug() << "getDetectionResult error:  "
                 << query.lastError();
    }
    return returnList;
}
