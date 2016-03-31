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

}

SearchDAO_Test::~SearchDAO_Test()
{
}

void SearchDAO_Test::initTestCase()
{
    projectShaeDatabase = QSqlDatabase::addDatabase("QSQLITE");

    QString folder = QStandardPaths::writableLocation(QStandardPaths::DataLocation);

    if(!folder.endsWith(QDir::separator()))
        folder.append(QDir::separator());

    QString name = "database.sqlite";

    QString base = folder.append(name);
    projectShaeDatabase.setDatabaseName(base);

    if(projectShaeDatabase.open())
    {
        qDebug() << "database connection succes" ;
    } else {
        qDebug() << "database connection error";
    }
}

void SearchDAO_Test::cleanupTestCase()
{
}

void SearchDAO_Test::testSimpleSearchDAO()
{

    SearchDAO sd = SearchDAO(&projectShaeDatabase);

    Search s = Search(QUuid::createUuid(),QTime(7,6), QGeoRectangle(QGeoCoordinate(5,6),QGeoCoordinate(4,3)), 5, 6);

    sd.dbSaveSearch(s);

    Search sback = sd.dbRetrieveSearch(s.getSearchID());

    QVERIFY(sback.getSearchID() == s.getSearchID());
    QVERIFY(s.getStartTime() == sback.getStartTime());
    QVERIFY(s.getArea().topLeft() == sback.getArea().topLeft());
    QVERIFY(s.getArea().bottomRight() == sback.getArea().bottomRight());
    QVERIFY(s.getHeight() == sback.getHeight());
    QVERIFY(s.getGimbalAngle() == sback.getGimbalAngle());


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
