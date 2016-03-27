#ifndef VIDEOSEQUENCEDAO_TEST_H
#define VIDEOSEQUENCEDAO_TEST_H

#include <QObject>
#include <iostream>
#include <QDebug>
#include <QtTest>
#include <string>
#include <QThread>
#include <QtSql>

#include "persistence/videosequencedao.h"

class VideoSequenceDAO_Test : public QObject
{
    Q_OBJECT

public:
    VideoSequenceDAO_Test(QSqlDatabase* db);
    ~VideoSequenceDAO_Test();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();

    /*! \brief Basic videosequencedao test
     */
    void testSimpleVideoSequenceDAO();
private:
    QSqlDatabase* projectShaeDatabase;
};

#endif // VIDEOSEQUENCEDAO_TEST_H
