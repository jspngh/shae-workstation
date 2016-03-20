#include "videosequencedao_test.h"
#include <QString>
#include <QtSql>
#include <QUuid>
#include <QtWidgets/QtWidgets>
#include <QtTest/QtTest>
#include "persistence/searchdao.h"
#include "models/search.h"

VideoSequenceDAO_Test::VideoSequenceDAO_Test()
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

VideoSequenceDAO_Test::~VideoSequenceDAO_Test()
{
    projectShaeDatabase.close();
}

void VideoSequenceDAO_Test::initTestCase()
{
}

void VideoSequenceDAO_Test::cleanupTestCase()
{
}

void VideoSequenceDAO_Test::testSimpleVideoSequenceDAO()
{
    //SearchDAO sd = SearchDAO(&projectShaeDatabase);

    //Search s = Search();
    //s.searchID = QUuid::createUuid();
    //s.start = QTime(7,6);

    //sd.dbSaveSearch(s);

    QVERIFY(true);

}
