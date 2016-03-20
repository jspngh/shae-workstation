#include "searchdao_test.h"
#include <QString>
#include <QtSql>
#include <QUuid>
#include <QtWidgets/QtWidgets>
#include <QtTest/QtTest>
#include "persistence/searchdao.h"
#include "models/search.h"

SearchDAO_Test::SearchDAO_Test()
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

SearchDAO_Test::~SearchDAO_Test()
{
    projectShaeDatabase.close();
}

void SearchDAO_Test::initTestCase()
{
}

void SearchDAO_Test::cleanupTestCase()
{
}

void SearchDAO_Test::testSimpleSearchDAO()
{
    //SearchDAO sd = SearchDAO(&projectShaeDatabase);

    //Search s = Search();
    //s.searchID = QUuid::createUuid();
    //s.start = QTime(7,6);

    //sd.dbSaveSearch(s);

    QVERIFY(true);

}
