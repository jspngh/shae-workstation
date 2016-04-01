#ifndef DRONESTATUSDAO_H
#define DRONESTATUSDAO_H

#include <QtSql>
#include <models/dronestatus.h>
#include <QUuid>
#include "generaldao.h"

/**
 * \brief The DroneStatusDAO class is responsible for loading and saving
 * dronestatus models into the database.
 */

class DroneStatusDAO : GeneralDAO
{
public:
    /**
     * \brief The basic constructor for a DroneStatusDAO needs a database as input.
     */
    DroneStatusDAO();
    DroneStatusDAO(QSqlDatabase *projectShaeDatabase);

    /**
     * \brief dbSaveDroneStatus saves a detection result into the database.
     * Its inputs are a droneid, searchid and dronestatus object.
     * Both ids are for referencing to tables in the database while de object is
     * the one that needs to be stored.
     */
    DroneStatus dbSaveDroneStatus(DroneStatus droneStatus, QUuid droneId, QUuid searchId);
    //compare with timestamp of workstation
    /**
     * \brief dbRetrieveDroneStatus Retrieves all the dronestatusses for a
     * certain drone and search and a certain interval.
     */
    QList<DroneStatus> dbRetrieveDroneStatus(QUuid droneId, QUuid searchId, QDateTime begin, QDateTime end);
    //retrieve latest dronestatus
    /**
     * \brief dbRetrieveDroneStatus Retrieves the most recent dronestatus for a
     * certain drone and search.
     */
    DroneStatus dbRetrieveDroneStatus(QUuid droneId, QUuid searchId);
    //retrieve dronestatus closest to time parameter
    /**
     * \brief dbRetrieveDroneStatus Retrieves the dronestatus for a
     * certain drone and search closest to a certain timestamp.
     */
    DroneStatus dbRetrieveDroneStatus(QUuid droneId, QUuid searchId, QDateTime time);
private:
    //database
    QSqlDatabase *projectShaeDatabase;
};

#endif // DRONESTATUSDAO_H
