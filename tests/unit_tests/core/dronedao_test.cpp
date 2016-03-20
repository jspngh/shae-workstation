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
    // not yet implemented due to drone model design wiht qobject
    QVERIFY(true);
}


