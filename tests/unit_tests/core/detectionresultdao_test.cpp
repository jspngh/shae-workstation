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
}

DetectionResultDAO_Test::~DetectionResultDAO_Test()
{

}

void DetectionResultDAO_Test::initTestCase()
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

void DetectionResultDAO_Test::cleanupTestCase()
{
}

void DetectionResultDAO_Test::testSimpleDetectionResultDAO()
{
    DetectionResultDAO sd = DetectionResultDAO(&projectShaeDatabase);

    DetectionResult *dr = new DetectionResult(QGeoCoordinate(5, 5), 5.5);
    QUuid searchID = QUuid::createUuid();
    QUuid droneID = QUuid::createUuid();

    sd.dbSaveDetectionResult(droneID, searchID, dr);

    QList<DetectionResult*>* sback = sd.dbRetrieveDetectionResults(droneID, searchID);

    QVERIFY(sback->first()->getScore() == dr->getScore());
    QVERIFY(dr->getLocation().longitude() == sback->first()->getLocation().longitude());
    QVERIFY(dr->getLocation().latitude() == sback->first()->getLocation().latitude());

    QSqlQuery query;
    query.prepare("DELETE from detectionresults "
                  "WHERE droneID == (:droneID)");
    query.bindValue(":droneID", droneID);
    if (query.exec()) {
        qDebug() << "delete succes";
    } else {
        qDebug() << "remove detectionresult error:  "
                 << query.lastError();
    };

}
