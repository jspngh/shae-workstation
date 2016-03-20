#include "dronedao_test.h"
#include <QString>
#include <QtSql>
#include <QUuid>
#include <QtWidgets/QtWidgets>
#include <QtTest/QtTest>
#include "persistence/searchdao.h"
#include "models/search.h"

DroneDAO_Test::DroneDAO_Test()
{
    projectShaeDatabase = QSqlDatabase::addDatabase("QSQLITE");
    projectShaeDatabase.setDatabaseName(QString("workstation/src/persistence/projectShae.db"));

    if (!projectShaeDatabase.open())
    {
       qDebug() << "Error: connection with database fail";
    }
    else
    {
       qDebug() << "Database: connection ok";
    }
}

DroneDAO_Test::~DroneDAO_Test()
{
    projectShaeDatabase.close();
}

void DroneDAO_Test::initTestCase()
{
}

void DroneDAO_Test::cleanupTestCase()
{
}

void DroneDAO_Test::testSimpleDroneDAO()
{
    //SearchDAO sd = SearchDAO(&projectShaeDatabase);

    //Search s = Search();
    //s.searchID = QUuid::createUuid();
    //s.start = QTime(7,6);

    //sd.dbSaveSearch(s);

    QVERIFY(true);

}


