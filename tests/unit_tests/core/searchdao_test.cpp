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
    SearchDAO sd = SearchDAO(&projectShaeDatabase);

    Search s = Search(QUuid::createUuid(),QTime(7,6));

    sd.dbSaveSearch(s);

    Search sback = sd.dbRetrieveSearch(s.getSearchID());

    QVERIFY(sback.getSearchID() == s.getSearchID() && s.getStart() == sback.getStart());

    QSqlQuery query;
    query.prepare("DELETE from searches "
                  "WHERE searchID == (:searchID)");
    query.bindValue(":searchID", s.getSearchID());
    if(query.exec())
    {
       qDebug() << "delete succes";
    }
    else
    {
       qDebug() << "addDroe error:  "
                << query.lastError();
    };
}
