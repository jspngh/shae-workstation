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
    query.bindValue(":searchID", searchId.toString());
    query.bindValue(":droneID", droneId.toString());
    query.bindValue(":timestampDrone", droneStatus.getTimestampDrone());
    query.bindValue(":timestampWorkstation", droneStatus.getTimestampRecievedWorkstation());
    QGeoCoordinate location = droneStatus.getCurrentLocation();
    query.bindValue(":latitude", location.latitude());
    query.bindValue(":longitude", location.longitude());
    query.bindValue(":altitude", location.longitude());
    query.bindValue(":orientation", droneStatus.getOrientation());
    query.bindValue(":gimballAngle", droneStatus.getCameraAngle());
    query.bindValue(":speed", droneStatus.getSpeed());
    query.bindValue(":batteryLevel", droneStatus.getBatteryLevel());
    query.bindValue(":droneState", droneStatus.getDroneState());
    if(query.exec())
    {
       qDebug() << "insert succes";
    }
    else
    {
       qDebug() << "addDetectionResult error:  "
                << query.lastError();
    }
    return droneStatus;
}

//compare with timestamp of workstation
QList<DroneStatus> DroneStatusDAO::dbRetrieveDroneStatus(QUuid droneId, QUuid searchId, QDateTime begin, QDateTime end)
{
    QSqlQuery query;
    QList<DroneStatus> returnList = QList<DroneStatus>();
    query.prepare("SELECT * FROM statuses where (searchID = (:searchID) and droneID = (:droneID)) order by timestampDrone");
    query.bindValue(":searchID", searchId);
    query.bindValue(":droneID", droneId);
    if(query.exec())
    {
        while (query.next()) {
            if(begin <= query.value(2).toDateTime() && query.value(2).toDateTime() <= end)
            {
                DroneStatus output = DroneStatus(query.value(2).toDateTime(), query.value(3).toDateTime(),
                                                 QGeoCoordinate(query.value(4).toDouble(), query.value(5).toDouble(), query.value(6).toDouble()),
                                                 query.value(7).toDouble(), query.value(8).toDouble(), query.value(9).toDouble(),
                                                 query.value(10).toDouble(), query.value(11).toInt());
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
    QList<DroneStatus> returnList = QList<DroneStatus>();
    query.prepare("SELECT * FROM statuses where (searchID = (:searchID) and droneID = (:droneID)) order by timestampDrone");
    query.bindValue(":searchID", searchId);
    query.bindValue(":droneID", droneId);
    if(query.exec())
    {
        while (query.next()) {
            DroneStatus output = DroneStatus(query.value(2).toDateTime(), query.value(3).toDateTime(),
                                             QGeoCoordinate(query.value(4).toDouble(), query.value(5).toDouble(), query.value(6).toDouble()),
                                             query.value(7).toDouble(), query.value(8).toDouble(), query.value(9).toDouble(),
                                             query.value(10).toDouble(), query.value(11).toInt());
            returnList.append(output);
        }
    }
    else
    {
       qDebug() << "getDetectionResult error:  "
                << query.lastError();
    }
    return returnList.back();
}

//retrieve dronestatus closest to time parameter
DroneStatus DroneStatusDAO::dbRetrieveDroneStatus(QUuid droneId, QUuid searchId, QDateTime time)
{
    QSqlQuery query;
    QList<DroneStatus> returnList = QList<DroneStatus>();
    query.prepare("SELECT * FROM statuses where (searchID = (:searchID) and droneID = (:droneID)) order by timestampDrone");
    query.bindValue(":searchID", searchId);
    query.bindValue(":droneID", droneId);
    if(query.exec())
    {
        while (query.next()) {
            if(query.value(3).toDateTime() < time)
            {
                DroneStatus output = DroneStatus(query.value(2).toDateTime(), query.value(3).toDateTime(),
                                                 QGeoCoordinate(query.value(4).toDouble(), query.value(5).toDouble(), query.value(6).toDouble()),
                                                 query.value(7).toDouble(), query.value(8).toDouble(), query.value(9).toDouble(),
                                                 query.value(10).toDouble(), query.value(11).toInt());
                returnList.append(output);
            }
        }
    }
    else
    {
       qDebug() << "getDetectionResult error:  "
                << query.lastError();
    }
    return returnList.back();
}
