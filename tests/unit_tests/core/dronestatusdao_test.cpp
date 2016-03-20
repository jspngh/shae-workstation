#include "dronestatusdao_test.h"
#include <QString>
#include <QtSql>
#include <QUuid>
#include <QtWidgets/QtWidgets>
#include <QtTest/QtTest>
#include "persistence/searchdao.h"
#include "models/search.h"

DroneStatusDAO_Test::DroneStatusDAO_Test()
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
    //SearchDAO sd = SearchDAO(&projectShaeDatabase);

    //Search s = Search();
    //s.searchID = QUuid::createUuid();
    //s.start = QTime(7,6);

    //sd.dbSaveSearch(s);

    QVERIFY(true);

}


