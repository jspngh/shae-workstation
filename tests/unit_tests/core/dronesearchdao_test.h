#ifndef DRONESEARCHDAO_TEST_H
#define DRONESEARCHDAO_TEST_H

#include <QObject>
#include <iostream>
#include <QDebug>
#include <QtTest>
#include <string>
#include <QThread>
#include <QtSql>

#include "persistence/dronesearchdao.h"

class DroneSearchDAO_Test : public QObject
{
    Q_OBJECT

public:
    DroneSearchDAO_Test(QSqlDatabase* db);
    ~DroneSearchDAO_Test();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();

    /*! \brief Basic dronesearchdao test
     */
    void testSimpleDroneSearchDAO();
private:
    QSqlDatabase* projectShaeDatabase;
};

#endif // DRONESEARCHDAO_TEST_H
