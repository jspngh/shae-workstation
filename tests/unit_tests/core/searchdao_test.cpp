#include "searchdao_test.h"
#include <QString>
#include <QtSql>
#include <QUuid>
#include <QtWidgets/QtWidgets>
#include <QtTest/QtTest>
#include <QGeoRectangle>
#include "persistence/searchdao.h"
#include "models/search.h"
#include <GeoPolygon.h>

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

void SearchDAO_Test::cleanupTestCase()
{
}

void SearchDAO_Test::testSimpleSearchDAO()
{

    SearchDAO sd = SearchDAO(&projectShaeDatabase);

    Search *s = new Search(QUuid::createUuid(), QTime(7, 6), new QGeoRectangle(QGeoCoordinate(5, 6), QGeoCoordinate(4, 3)), 5, 6, 7);

    sd.dbSaveSearch(s);

    Search *sback = sd.dbRetrieveSearch(s->getSearchID());

    QVERIFY(sback->getSearchID() == s->getSearchID());
    QVERIFY(s->getStartTime() == sback->getStartTime());
    QVERIFY(s->getArea()->type() == sback->getArea()->type());
    QGeoRectangle sArea = *(s->getArea()), sBackArea = *(sback->getArea());
    QVERIFY(sArea.topLeft() == sBackArea.topLeft());
    QVERIFY(sArea.bottomRight() == sBackArea.bottomRight());
    QVERIFY(s->getHeight() == sback->getHeight());
    QVERIFY(s->getGimbalAngle() == sback->getGimbalAngle());
    QVERIFY(s->getFpsProcessing() == sback->getFpsProcessing());


    QSqlQuery query;
    query.prepare("DELETE from searches "
                  "WHERE searchID == (:searchID)");
    query.bindValue(":searchID", s->getSearchID());
    if (query.exec()) {
        qDebug() << "delete succes";
    } else {
        qDebug() << "addSearch error:  "
                 << query.lastError();
    };
}

void SearchDAO_Test::testSimpleSearchPolyDAO()
{

    SearchDAO sd = SearchDAO(&projectShaeDatabase);
    QList<QGeoCoordinate> coordinates = QList<QGeoCoordinate>();
    coordinates.append(QGeoCoordinate(0, 1));
    coordinates.append(QGeoCoordinate(1, 0));
    coordinates.append(QGeoCoordinate(1, 1));
    coordinates.append(QGeoCoordinate(0, 0));

    Search *s = new Search(QUuid::createUuid(), QTime(7, 6), new GeoPolygon(coordinates), 5, 6, 7);

    sd.dbSaveSearch(s);

    Search *sback = sd.dbRetrieveSearch(s->getSearchID());

    QVERIFY(sback->getSearchID() == s->getSearchID());
    QVERIFY(s->getStartTime() == sback->getStartTime());
    QVERIFY(s->getArea()->type() == sback->getArea()->type());
    QGeoRectangle sArea = *(s->getArea()), sBackArea = *(sback->getArea());
    QVERIFY(sArea.topLeft() == sBackArea.topLeft());
    QVERIFY(sArea.bottomRight() == sBackArea.bottomRight());
    QVERIFY(s->getHeight() == sback->getHeight());
    QVERIFY(s->getGimbalAngle() == sback->getGimbalAngle());
    QVERIFY(s->getFpsProcessing() == sback->getFpsProcessing());


    QSqlQuery query;
    query.prepare("DELETE from searches "
                  "WHERE searchID == (:searchID)");
    query.bindValue(":searchID", s->getSearchID());
    if (query.exec()) {
        qDebug() << "delete succes";
    } else {
        qDebug() << "addSearch error:  "
                 << query.lastError();
    };
}
