#include "dronesearchdao_test.h"
#include <QString>
#include <QtSql>
#include <QUuid>
#include <QtWidgets/QtWidgets>
#include <QtTest/QtTest>
#include "persistence/dronesearchdao.h"

DroneSearchDAO_Test::DroneSearchDAO_Test()
{
}

DroneSearchDAO_Test::~DroneSearchDAO_Test()
{
}

void DroneSearchDAO_Test::initTestCase()
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

void DroneSearchDAO_Test::cleanupTestCase()
{
}

void DroneSearchDAO_Test::testSimpleDroneSearchDAO()
{
    DroneSearchDAO sd = DroneSearchDAO(&projectShaeDatabase);

    QList<QGeoCoordinate> s = QList<QGeoCoordinate>();
    for (int i = 0; i < 10; i ++)
        s.append(QGeoCoordinate(i, i));
    QUuid searchID = QUuid::createUuid();
    QUuid droneID = QUuid::createUuid();

    sd.dbSaveDronePath(droneID, searchID, s);

    QList<QGeoCoordinate> sback = sd.dbRetrieveDronePath(droneID, searchID);

    int i = 0;
    for (QGeoCoordinate coordinate : sback) {
        QVERIFY(i == coordinate.longitude());
        QVERIFY(i == coordinate.latitude());
        i++;
    }

    QSqlQuery query;
    query.prepare("DELETE from dronessearches "
                  "WHERE (droneID = (:droneID) and searchID = (:searchID))");
    query.bindValue(":droneID", droneID);
    query.bindValue(":searchID", searchID);
    if (query.exec()) {
        qDebug() << "delete succes";
    } else {
        qDebug() << "remove dronessearches error:  "
                 << query.lastError();
    };

}

