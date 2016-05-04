#ifndef DRONEDAO_TEST_H
#define DRONEDAO_TEST_H

#include <QObject>
#include <iostream>
#include <QDebug>
#include <QtTest>
#include <string>
#include <QThread>
#include <QtSql>

#include "persistence/dronedao.h"

class DroneDAO_Test : public QObject
{
    Q_OBJECT

public:
    DroneDAO_Test();
    ~DroneDAO_Test();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();

    /*! \brief Basic dronedao test
     */
    void testSimpleDroneDAO();
private:
    QSqlDatabase projectShaeDatabase;
};

#endif // DRONEDAO_TEST_H
