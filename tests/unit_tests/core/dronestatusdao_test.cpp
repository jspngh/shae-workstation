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
}

DroneStatusDAO_Test::~DroneStatusDAO_Test()
{
}

void DroneStatusDAO_Test::initTestCase()
{
    projectShaeDatabase = QSqlDatabase::addDatabase("QSQLITE");

    QString folder = QStandardPaths::writableLocation(QStandardPaths::DataLocation);

    if (!folder.endsWith(QDir::separator()))
        folder.append(QDir::separator());

    QString name = "database.sqlite";

    QString base = folder.append(name);
    projectShaeDatabase.setDatabaseName(base);

    if (projectShaeDatabase.open()) {
        qDebug() << "database connection succes" ;
    } else {
        qDebug() << "database connection error";
    }
}

void DroneStatusDAO_Test::cleanupTestCase()
{
}

void DroneStatusDAO_Test::testSimpleDroneStatusDAO()
{
    DroneStatusDAO sd = DroneStatusDAO(&projectShaeDatabase);

    DroneStatus one = DroneStatus(QDateTime(QDate(2016 , 5, 6) , QTime(5, 5, 5)), QDateTime(QDate(2016 , 5, 6) , QTime(5, 5, 6)), QGeoCoordinate(5, 5, 5), 5.5, 5.5, 5.5, 5.5, -123456789);
    DroneStatus two = DroneStatus(QDateTime(QDate(2016 , 5, 6) , QTime(6, 6, 6)), QDateTime(QDate(2016 , 5, 6) , QTime(6, 6, 7)), QGeoCoordinate(6, 6, 6), 5.5, 5.5, 5.5, 5.5, -123456789);
    DroneStatus three = DroneStatus(QDateTime(QDate(2016 , 5, 6) , QTime(7, 7, 7)), QDateTime(QDate(2016 , 5, 6) , QTime(7, 7, 8)), QGeoCoordinate(7, 7, 7), 5.5, 5.5, 5.5, 5.5, -123456789);
    DroneStatus four = DroneStatus(QDateTime(QDate(2016 , 5, 6) , QTime(8, 8, 8)), QDateTime(QDate(2016 , 5, 6) , QTime(8, 8, 9)), QGeoCoordinate(8, 8, 8), 5.5, 5.5, 5.5, 5.5, -123456789);

    DroneModule dm;
    one.setDrone(&dm);
    two.setDrone(&dm);
    three.setDrone(&dm);
    four.setDrone(&dm);

    sd.dbSaveDroneStatus(one);
    sd.dbSaveDroneStatus(two);
    sd.dbSaveDroneStatus(four);
    sd.dbSaveDroneStatus(three);

    QUuid droneID = dm.getGuid();

    QList<DroneStatus> sbackone = sd.dbRetrieveDroneStatus(droneID, QDateTime(QDate(2016 , 5, 6), QTime(6, 6, 6)), QDateTime(QDate(2016 , 5, 6), QTime(8, 8, 8)));

    for (DroneStatus dstatus : sbackone) {
        QVERIFY(dstatus.getTimestampDrone() >= QDateTime(QDate(2016 , 5, 6) , QTime(6, 6, 6)));
        QVERIFY(dstatus.getTimestampDrone() <= QDateTime(QDate(2016 , 5, 6) , QTime(8, 8, 8)));
    }

    DroneStatus mostRecent = sd.dbRetrieveDroneStatus(droneID);

    QVERIFY(mostRecent.getTimestampDrone() == four.getTimestampDrone());

    DroneStatus closest = sd.dbRetrieveDroneStatus(droneID, QDateTime(QDate(2016 , 5, 6) , QTime(7, 7, 7)));

    QVERIFY(closest.getTimestampDrone() == two.getTimestampDrone());

    QSqlQuery query;
    query.prepare("DELETE from statuses "
                  "WHERE droneState == (:droneState)");
    query.bindValue(":droneState", -123456789);
    if (query.exec()) {
        qDebug() << "delete succes";
    } else {
        qDebug() << "remove dronestatuses error:  "
                 << query.lastError();
    };
}


