#ifndef DRONEDAO_H
#define DRONEDAO_H

#include <QtSql>
#include <QGeoCoordinate>
#include <models/drone.h>
#include "generaldao.h"


/**
 * \brief The DroneDAO class is responsible for loading and saving
 * drone models into the database.
 */
class DroneDAO : GeneralDAO
{
public:
    /**
     * \brief The basic constructor for a DroneDAO needs a database as input.
     */
    DroneDAO();
    DroneDAO(QSqlDatabase *projectShaeDatabase);
    /**
     * \brief dbSaveDrone saves a detection result into the database.
     * Its inputs are a drone object.
     * The object is the one that needs to be stored.
     */
    Drone* dbSaveDrone(Drone *drone);
    /**
     * \brief dbRetrieveDrone Retrieves a drone for a
     * certain droneid.
     */
    Drone* dbRetrieveDrone(QUuid droneId);
private:
    QSqlDatabase *projectShaeDatabase;
};

#endif // DRONEDAO_H
