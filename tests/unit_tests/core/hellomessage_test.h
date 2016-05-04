#ifndef HELLOMESSAGE_TEST_H
#define HELLOMESSAGE_TEST_H

#include <QByteArray>
#include <QtTest/QtTest>
#include "models/hellomessage.h"


class HelloMessage_Test: public QObject
{
    Q_OBJECT
public:
    HelloMessage_Test();

private Q_SLOTS:
    void parse_test();
    void getters_test();
    void initTestCase();
    void cleanupTestCase();
};

#endif // HELLOMESSAGE_TEST_H
