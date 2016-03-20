#include "dronestatusdao_test.h"
#include <QString>
#include <QtSql>
#include <QUuid>
#include <QtWidgets/QtWidgets>
#include <QtTest/QtTest>
#include "persistence/dronestatusdao.h"
#include "models/dronestatus.h"

DroneStatusDAO_Test::DroneStatusDAO_Test()
{
    projectShaeDatabase = QSqlDatabase::addDatabase("QSQLITE");
    projectShaeDatabase.setDatabaseName(QString("/home/vpolflie/Documents/Eerst_Master_Computer_Wetenschappen/Design_Project/workstation/src/persistence/projectShae.db"));

    if (!projectShaeDatabase.open())
    {
       qDebug() << "Error: connection with database fail";
    }
    else
    {
       qDebug() << "Database: connection ok";
    }
}

DroneStatusDAO_Test::~DroneStatusDAO_Test()
{
    projectShaeDatabase.close();
}

void DroneStatusDAO_Test::initTestCase()
{
}

void DroneStatusDAO_Test::cleanupTestCase()
{
}

void DroneStatusDAO_Test::testSimpleDroneStatusDAO()
{
    DroneStatusDAO sd = DroneStatusDAO(&projectShaeDatabase);

    DroneStatus one = DroneStatus(QDateTime(QDate(2016 , 5, 6) ,QTime(5,5,5)), QDateTime(QDate(2016 , 5, 6) ,QTime(5,5,6)), QGeoCoordinate(5,5,5), 5.5, 5.5, 5.5, 5.5, -123456789);
    DroneStatus two = DroneStatus(QDateTime(QDate(2016 , 5, 6) ,QTime(6,6,6)), QDateTime(QDate(2016 , 5, 6) ,QTime(6,6,7)), QGeoCoordinate(6,6,6), 5.5, 5.5, 5.5, 5.5, -123456789);
    DroneStatus three = DroneStatus(QDateTime(QDate(2016 , 5, 6) ,QTime(7,7,7)), QDateTime(QDate(2016 , 5, 6) ,QTime(7,7,8)), QGeoCoordinate(7,7,7), 5.5, 5.5, 5.5, 5.5, -123456789);
    DroneStatus four = DroneStatus(QDateTime(QDate(2016 , 5, 6) ,QTime(8,8,8)), QDateTime(QDate(2016 , 5, 6) ,QTime(8,8,9)), QGeoCoordinate(8,8,8), 5.5, 5.5, 5.5, 5.5, -123456789);

    QUuid searchID = QUuid::createUuid();
    QUuid droneID = QUuid::createUuid();

    sd.dbSaveDroneStatus(one,droneID,searchID);
    sd.dbSaveDroneStatus(two,droneID,searchID);
    sd.dbSaveDroneStatus(four,droneID,searchID);
    sd.dbSaveDroneStatus(three,droneID,searchID);

   QList<DroneStatus> sbackone = sd.dbRetrieveDroneStatus(droneID,searchID,QDateTime(QDate(2016 , 5, 6), QTime(6,6,6)),QDateTime(QDate(2016 , 5, 6), QTime(8,8,8)));

   for(DroneStatus dstatus: sbackone){
       QVERIFY(dstatus.getTimestampDrone() >= QDateTime(QDate(2016 , 5, 6) ,QTime(6,6,6)));
       QVERIFY(dstatus.getTimestampDrone() <= QDateTime(QDate(2016 , 5, 6) ,QTime(8,8,8)));
   }

   DroneStatus mostRecent = sd.dbRetrieveDroneStatus(droneID,searchID);

   QVERIFY(mostRecent.getTimestampDrone() == four.getTimestampDrone());

   DroneStatus closest = sd.dbRetrieveDroneStatus(droneID, searchID, QDateTime(QDate(2016 , 5, 6) ,QTime(7,7,7)));

   QVERIFY(closest.getTimestampDrone() == two.getTimestampDrone());

   QSqlQuery query;
   query.prepare("DELETE from statuses "
                 "WHERE droneState == (:droneState)");
   query.bindValue(":droneState", -123456789);
   if(query.exec())
   {
      qDebug() << "delete succes";
   }
   else
   {
      qDebug() << "remove dronstatuses error:  "
               << query.lastError();
   };
}


