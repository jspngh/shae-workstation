#include "videosequencedao_test.h"
#include <QString>
#include <QtSql>
#include <QUuid>
#include <QtWidgets/QtWidgets>
#include <QtTest/QtTest>
#include "persistence/videosequencedao.h"
#include "models/videosequence.h"

VideoSequenceDAO_Test::VideoSequenceDAO_Test()
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

VideoSequenceDAO_Test::~VideoSequenceDAO_Test()
{
}

void VideoSequenceDAO_Test::initTestCase()
{
}

void VideoSequenceDAO_Test::cleanupTestCase()
{
}

void VideoSequenceDAO_Test::testSimpleVideoSequenceDAO()
{
    VideoSequenceDAO sd = VideoSequenceDAO(&projectShaeDatabase);

    VideoSequence s = VideoSequence(QUuid::createUuid(), QTime(8,8,8), QTime(9,9,9), 10 , "pathtofile");
    QUuid searchID = QUuid::createUuid();
    QUuid droneID = QUuid::createUuid();

    sd.dbSaveVideoSequence(droneID,searchID,s);

   VideoSequence sback = sd.dbRetrieveVideoSequence(droneID,searchID,s.getVideoID());

   QVERIFY(sback.getVideoID() == s.getVideoID());
   QVERIFY(s.getFrameCount() == sback.getFrameCount());
   QVERIFY(s.getStart() == sback.getStart());
   QVERIFY(s.getEnd() == sback.getEnd());
   QVERIFY(s.getPath() == sback.getPath());

    QSqlQuery query;
    query.prepare("DELETE from videosequences "
                  "WHERE videoID == (:videoID)");
    query.bindValue(":videoID", s.getVideoID());
    if(query.exec())
    {
       qDebug() << "delete succes";
    }
    else
    {
       qDebug() << "remove videosequence error:  "
                << query.lastError();
    };

}
