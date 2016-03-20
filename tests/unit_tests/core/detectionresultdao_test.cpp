#include "detectionresultdao_test.h"
#include <QString>
#include <QtSql>
#include <QUuid>
#include <QtWidgets/QtWidgets>
#include <QtTest/QtTest>
#include "persistence/searchdao.h"
#include "models/search.h"

DetectionResultDAO_Test::DetectionResultDAO_Test()
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

DetectionResultDAO_Test::~DetectionResultDAO_Test()
{
    projectShaeDatabase.close();
}

void DetectionResultDAO_Test::initTestCase()
{
}

void DetectionResultDAO_Test::cleanupTestCase()
{
}

void DetectionResultDAO_Test::testSimpleDetectionResultDAO()
{
    //SearchDAO sd = SearchDAO(&projectShaeDatabase);

    //Search s = Search();
    //s.searchID = QUuid::createUuid();
    //s.start = QTime(7,6);

    //sd.dbSaveSearch(s);

    QVERIFY(true);

}
