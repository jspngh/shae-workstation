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
    projectShaeDatabase.setDatabaseName("database.sqlite");
    if(projectShaeDatabase.open())
    {
        qDebug() << "database connection succes" ;
    } else {
        qDebug() << "database connection error";
    }
}

DroneDAO_Test::~DroneDAO_Test()
{
}

void DroneDAO_Test::initTestCase()
{
}

void DroneDAO_Test::cleanupTestCase()
{
}

void DroneDAO_Test::testSimpleDroneDAO()
{
    // not yet implemented due to drone model design wiht qobject
    QVERIFY(true);
}


