#include "dronesearchdao.h"

DroneSearchDAO::DroneSearchDAO()
{

}

DroneSearchDAO::DroneSearchDAO(QSqlDatabase* projectShaeDatabase){
    this->projectShaeDatabase = projectShaeDatabase;
}

QList<QGeoCoordinate> DroneSearchDAO::dbSaveDronePath(QUuid droneId, QUuid searchId, QList<QGeoCoordinate> path)
{
    QSqlQuery query;
    query.prepare("INSERT INTO dronessearches (searchID, droneID, path) "
                  "VALUES (:searchID, :droneID, :path)");
    query.bindValue(":searchID", searchId);
    query.bindValue(":droneID", droneId);

    QString pathString = QString("");

    for(QGeoCoordinate gc : path)
    {
        pathString.append(gc.latitude());
        pathString.append("-");
        pathString.append(gc.longitude());
        pathString.append(":");
    }
    query.bindValue(":path", pathString);
    if(query.exec())
    {
       qDebug() << "insert succes";
    }
    else
    {
       qDebug() << "addPath error:  "
                << query.lastError();
    }
    return path;
}

QList<QGeoCoordinate> DroneSearchDAO::dbRetrieveDronePath(QUuid droneId, QUuid searchId){
    QSqlQuery query;
    QList<QGeoCoordinate> returnList = QList<QGeoCoordinate>;
    query.prepare("SELECT path FROM dronessearches WHERE searchID = (:searchID) and droneID = (:droneID)");
    query.bindValue(":searchID", searchId);
    query.bindValue(":droneID", droneId);
    if(query.exec())
    {
        if(query.next()) {
            returnList = uncypherPathString(query.value(0));
        }
    }
    else
    {
       qDebug() << "getPath error:  "
                << query.lastError();
    }
    return returnList;
}

QList<QGeoCoordinate> DroneSearchDAO::uncypherPathString(QString pathString)
{
    QList<QGeoCoordinate> returnList = QList<QGeoCoordinate>;
    QList<QString> coordinates = pathString.split(":");
    for(QString coordinate : coordinates){
        QList<QString> coordinateValues = coordinate.split("-");
        returnList.append(QGeoCoordinate(coordinateValues.at(0).toDouble(),coordinateValues.at(1).toDouble()));
    }
    return returnList;
}
