#include "dronestatusdao.h"

DroneStatusDAO::DroneStatusDAO()
{

}

DroneStatusDAO::DroneStatusDAO(QSqlDatabase* projectShaeDatabase){
    this->projectShaeDatabase = projectShaeDatabase;
}

DroneStatus DroneStatusDAO::dbSaveDroneStatus(DroneStatus droneStatus, QUuid droneId, QUuid searchId)
{
    QSqlQuery query;
    query.prepare("INSERT INTO statuses (searchID, droneID, timestampDrone, timestampWorkstation, latitude, longitude, altitude, orientation, gimballAngle, speed, batteryLevel, droneState) "
                  "VALUES (:searchID, :droneID, :timestampDrone, :timestampWorkstation, :latitude, :longitude, :altitude, :orientation, :gimballAngle, :speed, :batteryLevel, :droneState)");
    query.bindValue(":searchID", searchId);
    query.bindValue(":droneID", droneId);
    QGeoCoordinate location = droneStatus.getPosition();
    query.bindValue(":latitude", location.latitude());
    query.bindValue(":longitude", location.longitude());
    query.bindValue(":altitude", location.longitude());
    query.bindValue(":orientation", droneStatus.getOrientation());
    query.bindValue(":gimballAngle", droneStatus.getGimballAngle());
    query.bindValue(":speed", droneStatus.getSpeed());
    query.bindValue(":batteryLevel", droneStatus.getBatteryLevel());
    query.bindValue(":droneState", droneStatus.getDroneState());
    query.bindValue(":timestampDrone", droneStatus.getTimestampDrone().toString());
    query.bindValue(":timestampWorkstation", droneStatus.getTimestampWorkstation().toString());
    if(query.exec())
    {
       qDebug() << "insert succes";
    }
    else
    {
       qDebug() << "addDetectionResult error:  "
                << query.lastError();
    }
    return result;
}

//compare with timestamp of workstation
QList<DroneStatus> DroneStatusDAO::dbRetrieveDroneStatus(QUuid droneId, QUuid searchId, QTime begin, QTime end)
{
    QSqlQuery query;
    QList<DroneStatus> returnList = QList<DroneStatus>;
    query.prepare("SELECT * FROM statuses");
    query.bindValue(":searchID", searchId);
    query.bindValue(":droneID", droneId);
    if(query.exec())
    {
        while (query.next()) {
            if(start <= QTime(query.value(2)) && QTime(query.value(3)) <= end)
            {
                DroneStatus output = DroneStatus(QTime(query.value(2)), QTime(query.value(3)), query.value(4), query.value(5), query.value(6),
                                                 query.value(7), query.value(8), query.value(9), query.value(10), query.value(11));
                returnList.append(output);
            }
        }
    }
    else
    {
       qDebug() << "getDetectionResult error:  "
                << query.lastError();
    }
    return returnList;
}

//retrieve latest dronestatus
DroneStatus DroneStatusDAO::dbRetrieveDroneStatus(QUuid droneId, QUuid searchId)
{
    QSqlQuery query;
    QList<DroneStatus> returnList = QList<DroneStatus>;
    query.prepare("SELECT * FROM statuses");
    query.bindValue(":searchID", searchId);
    query.bindValue(":droneID", droneId);
    if(query.exec())
    {
        while (query.next()) {
            DroneStatus output = DroneStatus(QTime(query.value(2)), QTime(query.value(3)), query.value(4), query.value(5), query.value(6),
                                                 query.value(7), query.value(8), query.value(9), query.value(10), query.value(11));
            returnList.append(output);
        }
    }
    else
    {
       qDebug() << "getDetectionResult error:  "
                << query.lastError();
    }
    return returnList.end();
}

//retrieve dronestatus closest to time parameter
DroneStatus DroneStatusDAO::dbRetrieveDroneStatus(QUuid droneId, QUuid searchId, QTime time)
{
    QSqlQuery query;
    QList<DroneStatus> returnList = QList<DroneStatus>;
    query.prepare("SELECT * FROM statuses");
    query.bindValue(":searchID", searchId);
    query.bindValue(":droneID", droneId);
    if(query.exec())
    {
        while (query.next()) {
            if(QTime(query.value(3)) < time)
            {
                DroneStatus output = DroneStatus(QTime(query.value(2)), QTime(query.value(3)), query.value(4), query.value(5), query.value(6),
                                                 query.value(7), query.value(8), query.value(9), query.value(10), query.value(11));
                returnList.append(output);
            }
        }
    }
    else
    {
       qDebug() << "getDetectionResult error:  "
                << query.lastError();
    }
    return returnList.end();
}
