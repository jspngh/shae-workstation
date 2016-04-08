#include "dronedao_test.h"
#include <QString>
#include <QtSql>
#include <QUuid>
#include <QtWidgets/QtWidgets>
#include <QtTest/QtTest>
#include "persistence/dronedao.h"
#include "models/drone.h"

DroneDAO_Test::DroneDAO_Test()
{
}

DroneDAO_Test::~DroneDAO_Test()
{
}

void DroneDAO_Test::initTestCase()
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

void DroneDAO_Test::cleanupTestCase()
{
}

void DroneDAO_Test::testSimpleDroneDAO()
{
    DroneDAO sd = DroneDAO(&projectShaeDatabase);

    Drone s = Drone(1, 2, "3", "4", "6",5.6);

    sd.dbSaveDrone(s);

    Drone sback = sd.dbRetrieveDrone(s.getGuid());

    QVERIFY(sback.getGuid() == s.getGuid());
    QVERIFY(sback.getDronePort() == s.getDronePort());
    QVERIFY(sback.getDroneIp() == s.getDroneIp());
    QVERIFY(sback.getControllerIp() == s.getControllerIp());
    QVERIFY(sback.getStreamPath() == s.getStreamPath());
    QVERIFY(sback.getStreamPort() == s.getStreamPort());
    QVERIFY(sback.getVisionWidth() == s.getVisionWidth());

    QSqlQuery query;
    query.prepare("DELETE from drones "
                  "WHERE droneID == (:droneID)");
    query.bindValue(":droneID", s.getGuid());
    if (query.exec()) {
        qDebug() << "delete succes";
    } else {
        qDebug() << "remove drone error:  "
                 << query.lastError();
    };
}
