#include "dronedao.h"

DroneDAO::DroneDAO()
{

}

DroneDAO::DroneDAO(QSqlDatabase* projectShaeDatabase){
    this->projectShaeDatabase = projectShaeDatabase;
}

Drone DroneDAO::dbSaveDrone(Drone drone)
{
    QSqlQuery query;
    query.prepare("INSERT INTO drones (droneID, visionWidth, dataPort, streamPort, serverIp, streamPath) "
                  "VALUES (:droneID, :visionWidth, :dataPort, :streamPort, :serverIp, :streamPath)");
    query.bindValue(":droneID", drone.getGuid());
    query.bindValue(":visionWidth", drone.getVisionWidth());
    query.bindValue(":dataPort", drone.getPortNr());
    query.bindValue(":streamPort", drone.getStreamPortNr());
    query.bindValue(":serverIp", drone.getServerIp());
    query.bindValue(":streamPath",drone.getStreamPath());
    if(query.exec())
    {
       qDebug() << "insert succes";
    }
    else
    {
       qDebug() << "addDrone error:  "
                << query.lastError();
    }
    return drone;
}

Drone DroneDAO::dbRetrieveDrone(QUuid droneId){
    QSqlQuery query;
    Drone returnDrone;
    query.prepare("SELECT dataPort, streamPort, serverIp, streamPath, visionWidth FROM drones WHERE droneID == (:droneID)");
    query.bindValue(":droneID", droneId);
    if(query.exec())
    {
        if (query.next()) {
            returnDrone = Drone(droneId, query.value(0).toInt(), query.value(1).toInt(),
                                query.value(2).toString(), query.value(3).toString(),
                                query.value(4).toDouble());
        }
    }
    else
    {
       qDebug() << "getDrone error:  "
                << query.lastError();
    }
    return returnDrone;
}
