#ifndef DRONESEARCHDAO_H
#define DRONESEARCHDAO_H

#include <QtSql>
#include <QGeoCoordinate>
#include "generaldao.h"

/**
 * \brief The DroneSearchDAO class is responsible for loading and saving
 * paths into the database.
 */
class DroneSearchDAO : GeneralDAO
{
public:
    /**
     * \brief The basic constructor for a DronesearchDAO needs a database as input.
     */
    DroneSearchDAO();
    DroneSearchDAO(QSqlDatabase *projectShaeDatabase);
    /**
     * \brief dbSaveDroneSearch saves a detection result into the database.
     * Its inputs are a droneid, searchid and coordinater list.
     * Both ids are for referencing to tables in the database while the list is
     * the one that needs to be stored.
     */
    QList<QGeoCoordinate>* dbSaveDronePath(QUuid droneId, QUuid searchId, QList<QGeoCoordinate>* path);
    /**
     * \brief dbRetrieveDroneSearch Retrieves the path for a
     * certain drone and search.
     */
    QList<QGeoCoordinate>* dbRetrieveDronePath(QUuid droneId, QUuid searchId);
    /**
     * \brief dbRetrieveDroneIds Retrieves the ids from the drones for a
     * certain search.
     */
    QList<QUuid>* dbRetrieveDroneIds(QUuid searchId);
private:
    QSqlDatabase *projectShaeDatabase;
};

#endif // DRONESEARCHDAO_H
