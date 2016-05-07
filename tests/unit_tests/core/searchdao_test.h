#ifndef SEARCHDAO_TEST_H
#define SEARCHDAO_TEST_H

#include <QObject>
#include <iostream>
#include <QDebug>
#include <QtTest>
#include <string>
#include <QThread>
#include <QtSql>

#include "persistence/searchdao.h"

class SearchDAO_Test : public QObject
{
    Q_OBJECT

public:
    SearchDAO_Test();
    ~SearchDAO_Test();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();

    /*! \brief Basic searchdao test
     */
    void testSimpleSearchDAO();
    void testSimpleSearchPolyDAO();
private:
    QSqlDatabase projectShaeDatabase;
};

#endif // SEARCHDAO_TEST_H
