#ifndef SYSTEM_TEST_H
#define SYSTEM_TEST_H

#include <QString>
#include <QProcess>
#include <QtTest/QtTest>
#include <QApplication>
#include "core/controller.h"
#include "ui/mainwindow.h"

class System_Test : public QObject
{
    Q_OBJECT

private:
    Controller * controller;

public:
    System_Test();
    ~System_Test();

signals:
    void startSearch(Search *s);

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void systemTest();
};


#endif // SYSTEM_TEST_H
