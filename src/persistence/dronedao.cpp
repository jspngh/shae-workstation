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
    query.prepare("INSERT INTO detectionresults (droneID, visionWidth) "
                  "VALUES (:droneID, :visionWidth)");
    query.bindValue(":droneID", drone.getDroneID());
    query.bindValue(":visionWidth", drone.getVisionWidth());
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
    query.prepare("SELECT visionWidth FROM drones WHERE droneID = (:droneID)");
    query.bindValue(":droneID", droneId);
    if(query.exec())
    {
        if (query.next()) {
            returnDrone = Drone(droneId, query.value(0));
        }
    }
    else
    {
       qDebug() << "getDrone error:  "
                << query.lastError();
    }
    return returnDrone;
}
