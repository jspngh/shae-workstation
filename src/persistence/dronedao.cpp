#include "dronedao.h"

DroneDAO::DroneDAO()
{

}

DroneDAO::DroneDAO(QSqlDatabase* projectShaeDatabase){
    this->projectShaeDatabase = projectShaeDatabase;
}

Drone DroneDAO::dbSaveDrone(Drone drone)
{
    /*QSqlQuery query;
    query.prepare("INSERT INTO detectionresults (droneID, visionWidth) "
                  "VALUES (:droneID, :visionWidth)");
    query.bindValue(":droneID", drone.getGuid());
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
    return drone;*/
    //TODO werkt nog niet aangezien men van het drone model een Q_Object hebben gemaakt
}

Drone DroneDAO::dbRetrieveDrone(QUuid droneId){
    /*QSqlQuery query;
    Drone returnDrone;
    query.prepare("SELECT visionWidth FROM drones WHERE droneID = (:droneID)");
    query.bindValue(":droneID", droneId);
    if(query.exec())
    {
        if (query.next()) {
            returnDrone = Drone(droneId,0,QString(" ") ,query.value(0).toDouble());
        }
    }
    else
    {
       qDebug() << "getDrone error:  "
                << query.lastError();
    }
    return returnDrone;*/
    //TODO werkt nog niet aangezien men van het drone model een Q_Object hebben gemaakt
}
