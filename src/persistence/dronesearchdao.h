#ifndef DRONESEARCHDAO_H
#define DRONESEARCHDAO_H

#include <QtSql>
#include <QGeoCoordinate>


class DroneSearchDAO
{
public:
    DroneSearchDAO();
    DroneSearchDAO(QSqlDatabase* projectShaeDatabase);
    QList<QGeoCoordinate> dbSaveDronePath(QUuid droneId, QUuid searchId, QList<QGeoCoordinate> path);
    QList<QGeoCoordinate> dbRetrieveDronePath(QUuid droneId, QUuid searchId);
private:
    QList<QGeoCoordinate> uncypherPathString(QString pathString);
    QSqlDatabase* projectShaeDatabase;
};

#endif // DRONESEARCHDAO_H
