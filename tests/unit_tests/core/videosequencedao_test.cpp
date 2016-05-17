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
}

VideoSequenceDAO_Test::~VideoSequenceDAO_Test()
{
}

void VideoSequenceDAO_Test::initTestCase()
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

void VideoSequenceDAO_Test::cleanupTestCase()
{
}

void VideoSequenceDAO_Test::testSimpleVideoSequenceDAO()
{
    VideoSequenceDAO sd = VideoSequenceDAO(&projectShaeDatabase);

    VideoSequence *s = new VideoSequence(QUuid::createUuid(), QTime(8, 8, 8), QTime(9, 9, 9), 10 , "pathtofile");
    QUuid searchID = QUuid::createUuid();
    QUuid droneID = QUuid::createUuid();

    sd.dbSaveVideoSequence(droneID, searchID, s);

    VideoSequence *sback = sd.dbRetrieveVideoSequence(droneID, searchID);

    QVERIFY(sback->getVideoID() == s->getVideoID());
    QVERIFY(s->getFrameCount() == sback->getFrameCount());
    QVERIFY(s->getStart() == sback->getStart());
    QVERIFY(s->getEnd() == sback->getEnd());
    QVERIFY(s->getPath() == sback->getPath());

    QSqlQuery query;
    query.prepare("DELETE from videosequences "
                  "WHERE videoID == (:videoID)");
    query.bindValue(":videoID", s->getVideoID());
    if (query.exec()) {
        qDebug() << "delete succes";
    } else {
        qDebug() << "remove videosequence error:  "
                 << query.lastError();
    };

}
