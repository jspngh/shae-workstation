#include "dronesearchdao.h"
#include <sstream>
#include <string>
#include <iostream>

DroneSearchDAO::DroneSearchDAO()
{

}

DroneSearchDAO::DroneSearchDAO(QSqlDatabase *projectShaeDatabase)
{
    this->projectShaeDatabase = projectShaeDatabase;
}

QList<QGeoCoordinate> DroneSearchDAO::dbSaveDronePath(QUuid droneId, QUuid searchId, QList<QGeoCoordinate> path)
{
    QSqlQuery query;
    query.prepare("INSERT INTO dronessearches (searchID, droneID, path) "
                  "VALUES (:searchID, :droneID, :path)");
    query.bindValue(":searchID", searchId);
    query.bindValue(":droneID", droneId);

    std::ostringstream os;

    for (QGeoCoordinate gc : path) {
        os << gc.latitude() << "-" << gc.longitude() << ":";
    }

    QString pathString = QString(os.str().c_str());

    query.bindValue(":path", pathString);
    if (query.exec()) {
        qDebug() << "insert path succes";
    } else {
        qDebug() << "addPath error:  "
                 << query.lastError();
    }
    return path;
}

QList<QGeoCoordinate> DroneSearchDAO::dbRetrieveDronePath(QUuid droneId, QUuid searchId)
{
    QSqlQuery query;
    QList<QGeoCoordinate> returnList = QList<QGeoCoordinate>();
    query.prepare("SELECT path FROM dronessearches WHERE searchID = (:searchID) and droneID = (:droneID)");
    query.bindValue(":searchID", searchId);
    query.bindValue(":droneID", droneId);
    if (query.exec()) {
        if (query.next()) {
            returnList = uncypherPathString(query.value(0).toString());
        }
    } else {
        qDebug() << "getPath error:  "
                 << query.lastError();
    }
    return returnList;
}

