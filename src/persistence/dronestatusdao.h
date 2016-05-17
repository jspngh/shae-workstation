#ifndef DRONESTATUSDAO_H
#define DRONESTATUSDAO_H

#include <QUuid>
#include <QtSql>
#include "generaldao.h"
#include <communication/dronemodule.h>
#include <models/dronestatus.h>

/**
 * \brief The DroneStatusDAO class is responsible for loading and saving
 * dronestatus models into the database.
 * \ingroup Persistence
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
     * Its input is a dronestatus object.
     * This object is the one that needs to be stored.
     */
    DroneStatus *dbSaveDroneStatus(DroneStatus *droneStatus);
    //compare with timestamp of workstation
    /**
     * \brief dbRetrieveDroneStatus Retrieves all the dronestatusses for a
     * certain drone and a certain interval.
     */
    QList<DroneStatus *> *dbRetrieveDroneStatus(QUuid droneId, QDateTime begin, QDateTime end);
    //retrieve latest dronestatus
    /**
     * \brief dbRetrieveDroneStatus Retrieves the most recent dronestatus for a
     * certain drone.
     */
    DroneStatus *dbRetrieveDroneStatus(QUuid droneId);
    //retrieve dronestatus closest to time parameter
    /**
     * \brief dbRetrieveDroneStatus Retrieves the dronestatus for a
     * certain drone closest to a certain timestamp.
     */
    DroneStatus *dbRetrieveDroneStatus(QUuid droneId, QDateTime time);
private:
    //database
    QSqlDatabase *projectShaeDatabase;

    QList<DroneStatus *> *retrieveQuery(QSqlQuery query);
};

#endif // DRONESTATUSDAO_H
