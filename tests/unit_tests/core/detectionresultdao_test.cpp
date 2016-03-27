#include "detectionresultdao_test.h"
#include <QString>
#include <QtSql>
#include <QUuid>
#include <QtWidgets/QtWidgets>
#include <QtTest/QtTest>
#include "persistence/searchdao.h"
#include "models/search.h"

DetectionResultDAO_Test::DetectionResultDAO_Test(QSqlDatabase* db)
{
    projectShaeDatabase = db;
}

DetectionResultDAO_Test::~DetectionResultDAO_Test()
{

}

void DetectionResultDAO_Test::initTestCase()
{
}

void DetectionResultDAO_Test::cleanupTestCase()
{
}

void DetectionResultDAO_Test::testSimpleDetectionResultDAO()
{
    DetectionResultDAO sd = DetectionResultDAO(projectShaeDatabase);

    DetectionResult s = DetectionResult(QGeoCoordinate(5,5), 5.5, VideoSequence(QUuid::createUuid()));
    QUuid searchID = QUuid::createUuid();
    QUuid droneID = QUuid::createUuid();

    sd.dbSaveDetectionResult(droneID,searchID,s);

   QList<DetectionResult> sback = sd.dbRetrieveDetectionResults(droneID,searchID);

   QVERIFY(sback.first().getScore() == s.getScore());
   QVERIFY( s.getVideoSequence().getVideoID() == sback.first().getVideoSequence().getVideoID());
   QVERIFY(s.getLocation().longitude() == sback.first().getLocation().longitude());
   QVERIFY(s.getLocation().latitude() == sback.first().getLocation().latitude());

    QSqlQuery query;
    query.prepare("DELETE from detectionresults "
                  "WHERE videoID == (:videoID)");
    query.bindValue(":videoID", s.getVideoSequence().getVideoID());
    if(query.exec())
    {
       qDebug() << "delete succes";
    }
    else
    {
       qDebug() << "remove detectionresult error:  "
                << query.lastError();
    };

}
