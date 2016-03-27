#ifndef DRONESTATUSDAO_TEST_H
#define DRONESTATUSDAO_TEST_H

#include <QObject>
#include <iostream>
#include <QDebug>
#include <QtTest>
#include <string>
#include <QThread>
#include <QtSql>

#include "persistence/dronestatusdao.h"

class DroneStatusDAO_Test : public QObject
{
    Q_OBJECT

public:
    DroneStatusDAO_Test(QSqlDatabase* db);
    ~DroneStatusDAO_Test();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();

    /*! \brief Basic dronestatusdao test
     */
    void testSimpleDroneStatusDAO();
private:
    QSqlDatabase* projectShaeDatabase;
};

#endif // DRONESTATUSDAO_TEST_H
