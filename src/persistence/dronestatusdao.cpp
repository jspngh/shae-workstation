#include "dronestatusdao.h"
#include <sstream>
#include <string>
#include <iostream>


DroneStatusDAO::DroneStatusDAO()
{

}

DroneStatusDAO::DroneStatusDAO(QSqlDatabase* projectShaeDatabase){
    this->projectShaeDatabase = projectShaeDatabase;
}

DroneStatus DroneStatusDAO::dbSaveDroneStatus(DroneStatus droneStatus, QUuid droneId, QUuid searchId)
{
    QSqlQuery query;
    query.prepare("INSERT INTO statuses (searchID, droneID, timestampDrone,"
                  "timestampReceivedWorkstation, latitude, longitude,"
                  "orientation, cameraAngle, speed, selectedSpeed, height, "
                  "selectedHeight, batteryLevel, fps, resolution,"
                  "heartbeat, droneState, manufacturer, droneType, "
                  "nextWaypointLongitude, nextWaypointLatitude, previousWaypointLongitude,"
                  " previousWaypointLatitude, nextWaypoints) "
                  "VALUES (:searchID, :droneID, :timestampDrone,"
                  ":timestampReceivedWorkstation, :latitude, :longitude,"
                  ":orientation, :cameraAngle, :speed, :selectedSpeed, :height, "
                  ":selectedHeight, :batteryLevel, :fps, :resolution,"
                  ":heartbeat, :droneState, :manufacturer, :droneType, "
                  ":nextWaypointLongitude, :nextWaypointLatitude, :previousWaypointLongitude,"
                  " :previousWaypointLatitude, :nextWaypoints) ");
    query.bindValue(":searchID", searchId);
    query.bindValue(":droneID", droneId);
    query.bindValue(":timestampDrone", droneStatus.getTimestampDrone());
    query.bindValue(":timestampWorkstation", droneStatus.getTimestampRecievedWorkstation());
    QGeoCoordinate location = droneStatus.getCurrentLocation();
    query.bindValue(":latitude", location.latitude());
    query.bindValue(":longitude", location.longitude());
    query.bindValue(":orientation", droneStatus.getOrientation());
    query.bindValue(":cameraAngle", droneStatus.getCameraAngle());
    query.bindValue(":speed", droneStatus.getSpeed());
    query.bindValue(":batteryLevel", droneStatus.getBatteryLevel());
    query.bindValue(":droneState", droneStatus.getDroneState());
    query.bindValue(":selectedSpeed", droneStatus.getSelectedSpeed());
    query.bindValue(":height",droneStatus.getHeight());
    query.bindValue(":selectedHeight",droneStatus.getSelectedHeight());
    query.bindValue(":fps",droneStatus.getFps());
    query.bindValue(":resolution",droneStatus.getResolution());
    query.bindValue(":heartbeat",droneStatus.getHeartbeat());
    query.bindValue(":manufacturer",droneStatus.getManufacturer());
    query.bindValue(":droneType",droneStatus.getType());
    query.bindValue(":nextWaypointLongitude",droneStatus.getNextWaypoint().longitude());
    query.bindValue(":nextWaypointLatitude",droneStatus.getNextWaypoint().latitude());
    query.bindValue(":previousWaypointLongitude",droneStatus.getPreviousWaypoint().longitude());
    query.bindValue(":previousWaypointLatitude",droneStatus.getPreviousWaypoint().latitude());

    std::ostringstream os;

    for(QGeoCoordinate gc : droneStatus.getNextWaypoints())
    {
        os << gc.latitude() << "-" << gc.longitude() << ":";
    }

    QString pathString = QString(os.str().c_str());


    query.bindValue(":nextWaypoints", pathString);
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
                QList<QGeoCoordinate> nextWaypoints = uncypherPathString(query.value(23).toString());
                DroneStatus output = DroneStatus(query.value(2).toDateTime(), query.value(3).toDateTime(),
                                                 QGeoCoordinate(query.value(4).toDouble(), query.value(5).toDouble()),
                                                 query.value(6).toDouble(), query.value(7).toDouble(), query.value(8).toDouble() ,
                                                 query.value(9).toDouble() , query.value(10).toDouble() , query.value(11).toDouble() ,
                                                 query.value(12).toDouble() , query.value(13).toInt() , query.value(14).toInt(),
                                                 query.value(15).toBool(), query.value(16).toInt(), query.value(17).toString(),
                                                 query.value(18).toString(),
                                                 QGeoCoordinate(query.value(20).toDouble(), query.value(19).toDouble()),
                                                 QGeoCoordinate(query.value(22).toDouble(), query.value(21).toDouble()),
                                                 nextWaypoints);
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
            QList<QGeoCoordinate> nextWaypoints = uncypherPathString(query.value(23).toString());
            DroneStatus output = DroneStatus(query.value(2).toDateTime(), query.value(3).toDateTime(),
                                             QGeoCoordinate(query.value(4).toDouble(), query.value(5).toDouble()),
                                             query.value(6).toDouble(), query.value(7).toDouble(), query.value(8).toDouble() ,
                                             query.value(9).toDouble() , query.value(10).toDouble() , query.value(11).toDouble() ,
                                             query.value(12).toDouble() , query.value(13).toInt() , query.value(14).toInt(),
                                             query.value(15).toBool(), query.value(16).toInt(), query.value(17).toString(),
                                             query.value(18).toString(),
                                             QGeoCoordinate(query.value(20).toDouble(), query.value(19).toDouble()),
                                             QGeoCoordinate(query.value(22).toDouble(), query.value(21).toDouble()),
                                             nextWaypoints);
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
            if(query.value(2).toDateTime() < time)
            {
                QList<QGeoCoordinate> nextWaypoints = uncypherPathString(query.value(23).toString());
                DroneStatus output = DroneStatus(query.value(2).toDateTime(), query.value(3).toDateTime(),
                                                 QGeoCoordinate(query.value(4).toDouble(), query.value(5).toDouble()),
                                                 query.value(6).toDouble(), query.value(7).toDouble(), query.value(8).toDouble() ,
                                                 query.value(9).toDouble() , query.value(10).toDouble() , query.value(11).toDouble() ,
                                                 query.value(12).toDouble() , query.value(13).toInt() , query.value(14).toInt(),
                                                 query.value(15).toBool(), query.value(16).toInt(), query.value(17).toString(),
                                                 query.value(18).toString(),
                                                 QGeoCoordinate(query.value(20).toDouble(), query.value(19).toDouble()),
                                                 QGeoCoordinate(query.value(22).toDouble(), query.value(21).toDouble()),
                                                 nextWaypoints);
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
