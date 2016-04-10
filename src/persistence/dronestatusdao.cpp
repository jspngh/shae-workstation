#include "dronestatusdao.h"
#include <sstream>
#include <string>
#include <iostream>


DroneStatusDAO::DroneStatusDAO()
{

}

DroneStatusDAO::DroneStatusDAO(QSqlDatabase *projectShaeDatabase)
{
    this->projectShaeDatabase = projectShaeDatabase;
}

DroneStatus DroneStatusDAO::dbSaveDroneStatus(DroneStatus droneStatus)
{
    QSqlQuery query;
    query.prepare("INSERT INTO statuses (droneID, timestampDrone,"
                  "timestampReceivedWorkstation, latitude, longitude,"
                  "orientation, cameraAngle, speed, selectedSpeed, height, "
                  "selectedHeight, batteryLevel, fps, resolution,"
                  "heartbeat, droneState, manufacturer, droneType, "
                  "nextWaypointLongitude, nextWaypointLatitude, previousWaypointOrder,"
                  "nextWaypoints) "
                  "VALUES (:droneID, :timestampDrone,"
                  ":timestampReceivedWorkstation, :latitude, :longitude,"
                  ":orientation, :cameraAngle, :speed, :selectedSpeed, :height, "
                  ":selectedHeight, :batteryLevel, :fps, :resolution,"
                  ":heartbeat, :droneState, :manufacturer, :droneType, "
                  ":nextWaypointLongitude, :nextWaypointLatitude, :previousWaypointOrder,"
                  ":nextWaypoints) ");
    query.bindValue(":droneID", droneStatus.getDrone()->getGuid());
    query.bindValue(":timestampDrone", droneStatus.getTimestampDrone());
    query.bindValue(":timestampWorkstation", droneStatus.getTimestampReceivedWorkstation());
    QGeoCoordinate location = droneStatus.getCurrentLocation();
    query.bindValue(":latitude", location.latitude());
    query.bindValue(":longitude", location.longitude());
    query.bindValue(":orientation", droneStatus.getOrientation());
    query.bindValue(":cameraAngle", droneStatus.getCameraAngle());
    query.bindValue(":speed", droneStatus.getSpeed());
    query.bindValue(":batteryLevel", droneStatus.getBatteryLevel());
    query.bindValue(":droneState", droneStatus.getDroneState());
    query.bindValue(":selectedSpeed", droneStatus.getSelectedSpeed());
    query.bindValue(":height", droneStatus.getHeight());
    query.bindValue(":selectedHeight", droneStatus.getSelectedHeight());
    query.bindValue(":fps", droneStatus.getFps());
    query.bindValue(":resolution", droneStatus.getResolution());
    query.bindValue(":heartbeat", droneStatus.getHeartbeat());
    query.bindValue(":manufacturer", droneStatus.getManufacturer());
    query.bindValue(":droneType", droneStatus.getType());
    query.bindValue(":nextWaypointLongitude", droneStatus.getNextWaypoint().longitude());
    query.bindValue(":nextWaypointLatitude", droneStatus.getNextWaypoint().latitude());
    query.bindValue(":previousWaypointOrder", droneStatus.getPreviousWaypointOrder());

    std::ostringstream os;

    for (QGeoCoordinate gc : droneStatus.getNextWaypoints()) {
        os << gc.latitude() << "-" << gc.longitude() << ":";
    }

    QString pathString = QString(os.str().c_str());


    query.bindValue(":nextWaypoints", pathString);
    if (query.exec()) {
        qDebug() << "insert status succes with time " << droneStatus.getTimestampDrone();
    } else {
        qDebug() << "addDroneStatus error:  "
                 << query.lastError();
    }
    return droneStatus;
}

//compare with timestamp of workstation
QList<DroneStatus> DroneStatusDAO::dbRetrieveDroneStatus(QUuid droneId, QDateTime begin, QDateTime end)
{
    QSqlQuery query;
    QList<DroneStatus> returnList = QList<DroneStatus>();
    query.prepare("SELECT * FROM statuses where droneID = (:droneID) order by timestampDrone");
    query.bindValue(":droneID", droneId);
    if (query.exec()) {
        while (query.next()) {
            if (begin <= query.value(1).toDateTime() && query.value(1).toDateTime() <= end) {
                QList<QGeoCoordinate> nextWaypoints = uncypherPathString(query.value(21).toString());
                DroneStatus output = DroneStatus(query.value(1).toDateTime(), query.value(2).toDateTime(),
                                                 QGeoCoordinate(query.value(3).toDouble(), query.value(4).toDouble()),
                                                 query.value(5).toDouble(), query.value(6).toDouble(), query.value(7).toDouble() ,
                                                 query.value(8).toDouble() , query.value(9).toDouble() , query.value(10).toDouble() ,
                                                 query.value(11).toDouble() , query.value(12).toInt() , query.value(13).toInt(),
                                                 query.value(14).toBool(), query.value(15).toInt(), query.value(16).toString(),
                                                 query.value(17).toString(),
                                                 QGeoCoordinate(query.value(19).toDouble(), query.value(18).toDouble()),
                                                 query.value(20).toInt(),
                                                 nextWaypoints);
                returnList.append(output);
            }
        }
    } else {
        qDebug() << "getDronestatus error:  "
                 << query.lastError();
    }
    return returnList;
}

//retrieve latest dronestatus
DroneStatus DroneStatusDAO::dbRetrieveDroneStatus(QUuid droneId)
{
    QSqlQuery query;
    QList<DroneStatus> returnList = QList<DroneStatus>();
    query.prepare("SELECT * FROM statuses where droneID = (:droneID) order by timestampDrone");
    query.bindValue(":droneID", droneId);
    if (query.exec()) {
        while (query.next()) {
            QList<QGeoCoordinate> nextWaypoints = uncypherPathString(query.value(21).toString());
            DroneStatus output = DroneStatus(query.value(1).toDateTime(), query.value(2).toDateTime(),
                                             QGeoCoordinate(query.value(3).toDouble(), query.value(4).toDouble()),
                                             query.value(5).toDouble(), query.value(6).toDouble(), query.value(7).toDouble() ,
                                             query.value(8).toDouble() , query.value(9).toDouble() , query.value(10).toDouble() ,
                                             query.value(11).toDouble() , query.value(12).toInt() , query.value(13).toInt(),
                                             query.value(14).toBool(), query.value(15).toInt(), query.value(16).toString(),
                                             query.value(17).toString(),
                                             QGeoCoordinate(query.value(19).toDouble(), query.value(18).toDouble()),
                                             query.value(20).toInt(),
                                             nextWaypoints);
            returnList.append(output);
        }
    } else {
        qDebug() << "getDronestatus error:  "
                 << query.lastError();
    }
    return returnList.back();
}

//retrieve dronestatus closest to time parameter
DroneStatus DroneStatusDAO::dbRetrieveDroneStatus(QUuid droneId, QDateTime time)
{
    QSqlQuery query;
    QList<DroneStatus> returnList = QList<DroneStatus>();
    query.prepare("SELECT * FROM statuses where droneID = (:droneID) order by timestampDrone");
    query.bindValue(":droneID", droneId);
    if (query.exec()) {
        while (query.next()) {
            if (query.value(1).toDateTime() < time) {
                QList<QGeoCoordinate> nextWaypoints = uncypherPathString(query.value(21).toString());
                DroneStatus output = DroneStatus(query.value(1).toDateTime(), query.value(2).toDateTime(),
                                                 QGeoCoordinate(query.value(3).toDouble(), query.value(4).toDouble()),
                                                 query.value(5).toDouble(), query.value(6).toDouble(), query.value(7).toDouble() ,
                                                 query.value(8).toDouble() , query.value(9).toDouble() , query.value(10).toDouble() ,
                                                 query.value(11).toDouble() , query.value(12).toInt() , query.value(13).toInt(),
                                                 query.value(14).toBool(), query.value(15).toInt(), query.value(16).toString(),
                                                 query.value(17).toString(),
                                                 QGeoCoordinate(query.value(19).toDouble(), query.value(18).toDouble()),
                                                 query.value(20).toInt(),
                                                 nextWaypoints);
                returnList.append(output);
            }
        }
    } else {
        qDebug() << "getDronestatus error:  "
                 << query.lastError();
        qDebug() << "a bogus VideoSequence was created, which is necessary for unit and integration tests";
        return DroneStatus();
    }
    if(returnList.size()>0)
    {
        return returnList.back();
    }
    else
    {
        qDebug() << "a bogus VideoSequence was created, because the DroneStatusDAO has failed";
        return DroneStatus();
    }
}
