#ifndef DRONESTATUSDAO_H
#define DRONESTATUSDAO_H

#include <QtSql>
#include <models/dronestatus.h>
#include <QUuid>

class DroneStatusDAO
{
public:
    DroneStatusDAO();
    DroneStatusDAO(QSqlDatabase* projectShaeDatabase);

    DroneStatus dbSaveDroneStatus(DroneStatus droneStatus, QUuid droneId, QUuid searchId);
    //compare with timestamp of workstation
    QList<DroneStatus> dbRetrieveDroneStatus(QUuid droneId, QUuid searchId, QTime begin, QTime end);
    //retrieve latest dronestatus
    DroneStatus dbRetrieveDroneStatus(QUuid droneId, QUuid searchId);
    //retrieve dronestatus closest to time parameter
    DroneStatus dbRetrieveDroneStatus(QUuid droneId, QUuid searchId, QTime time);
private:
    QSqlDatabase* projectShaeDatabase;
};

#endif // DRONESTATUSDAO_H
