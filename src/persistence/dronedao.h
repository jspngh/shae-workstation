#ifndef DRONEDAO_H
#define DRONEDAO_H

#include <QtSql>
#include <QGeoCoordinate>
#include <models/drone.h>

class DroneDAO
{
public:
    DroneDAO();
    DroneDAO(QSqlDatabase* projectShaeDatabase);

    Drone dbSaveDrone(Drone drone);
    Drone dbRetrieveDrone(QUuid droneId);
private:
    QSqlDatabase* projectShaeDatabase;
};

#endif // DRONEDAO_H
