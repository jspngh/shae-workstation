#include "dronedao_test.h"
#include <QString>
#include <QtSql>
#include <QUuid>
#include <QtWidgets/QtWidgets>
#include <QtTest/QtTest>
#include "persistence/searchdao.h"
#include "models/search.h"

DroneDAO_Test::DroneDAO_Test(QSqlDatabase* db)
{
    projectShaeDatabase = db;
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


