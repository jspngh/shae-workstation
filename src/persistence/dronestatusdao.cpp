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
    QGeoCoordinate location = droneStatus.getCurrentLocation();
    query.bindValue(":latitude", location.latitude());
    query.bindValue(":longitude", location.longitude());
    query.bindValue(":altitude", location.longitude());
    query.bindValue(":orientation", droneStatus.getOrientation());
    query.bindValue(":gimballAngle", droneStatus.getCameraAngle());
    query.bindValue(":speed", droneStatus.getSpeed());
    query.bindValue(":batteryLevel", droneStatus.getBatteryLevel());
    query.bindValue(":droneState", droneStatus.getDroneState());
    query.bindValue(":timestampDrone", droneStatus.getTimestampDrone().toString());
    query.bindValue(":timestampWorkstation", droneStatus.getTimestampRecievedWorkstation().toString());
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
QList<DroneStatus> DroneStatusDAO::dbRetrieveDroneStatus(QUuid droneId, QUuid searchId, QTime begin, QTime end)
{
    QSqlQuery query;
    QList<DroneStatus> returnList = QList<DroneStatus>();
    query.prepare("SELECT * FROM statuses");
    query.bindValue(":searchID", searchId);
    query.bindValue(":droneID", droneId);
    if(query.exec())
    {
        while (query.next()) {
            if(begin <= query.value(2).toTime() && query.value(3).toTime() <= end)
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
    query.prepare("SELECT * FROM statuses");
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
DroneStatus DroneStatusDAO::dbRetrieveDroneStatus(QUuid droneId, QUuid searchId, QTime time)
{
    QSqlQuery query;
    QList<DroneStatus> returnList = QList<DroneStatus>();
    query.prepare("SELECT * FROM statuses");
    query.bindValue(":searchID", searchId);
    query.bindValue(":droneID", droneId);
    if(query.exec())
    {
        while (query.next()) {
            if(query.value(3).toTime() < time)
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
