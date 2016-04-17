#include "dronedao.h"

DroneDAO::DroneDAO()
{

}

DroneDAO::DroneDAO(QSqlDatabase *projectShaeDatabase)
{
    this->projectShaeDatabase = projectShaeDatabase;
}

Drone* DroneDAO::dbSaveDrone(Drone *drone)
{
    QSqlQuery query;
    query.prepare("INSERT INTO drones (droneID, visionWidth, dronePort, streamPort, droneIp, controllerIp, streamPath) "
                  "VALUES (:droneID, :visionWidth, :dronePort, :streamPort, :droneIp, :controllerIp, :streamPath)");
    query.bindValue(":droneID", drone->getGuid());
    query.bindValue(":visionWidth", drone->getVisionWidth());
    query.bindValue(":dronePort", drone->getDronePort());
    query.bindValue(":streamPort", drone->getStreamPort());
    query.bindValue(":droneIp", drone->getDroneIp());
    query.bindValue(":controllerIp", drone->getControllerIp());
    query.bindValue(":streamPath", drone->getStreamPath());
    if (query.exec()) {
        qDebug() << "insert drone succes";
    } else {
        qDebug() << "addDrone error:  "
                 << query.lastError();
    }
    return drone;
}

Drone* DroneDAO::dbRetrieveDrone(QUuid droneId)
{
    QSqlQuery query;
    Drone *returnDrone;
    query.prepare("SELECT dronePort, streamPort, droneIp, controllerIp, streamPath, visionWidth FROM drones WHERE droneID == (:droneID)");
    query.bindValue(":droneID", droneId);
    if (query.exec()) {
        if (query.next()) {
            returnDrone = new Drone(droneId, query.value(0).toInt(), query.value(1).toInt(),
                                query.value(2).toString(), query.value(3).toString(),
                                query.value(4).toString(), query.value(5).toDouble());
        }
    } else {
        qDebug() << "getDrone error:  "
                 << query.lastError();
    }
    return returnDrone;
}
