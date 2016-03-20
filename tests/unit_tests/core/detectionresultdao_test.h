#ifndef DETECTIONRESULTDAO_TEST_H
#define DETECTIONRESULTDAO_TEST_H

#include <QObject>
#include <iostream>
#include <QDebug>
#include <QtTest>
#include <string>
#include <QThread>
#include <QtSql>

#include "persistence/detectionresultdao.h"

class DetectionResultDAO_Test : public QObject
{
    Q_OBJECT

public:
    DetectionResultDAO_Test();
    ~DetectionResultDAO_Test();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();

    /*! \brief Basic detectionresultdao test
     */
    void testSimpleDetectionResultDAO();
private:
    QSqlDatabase projectShaeDatabase;
};

#endif // DETECTIONRESULTDAO_TEST_H
