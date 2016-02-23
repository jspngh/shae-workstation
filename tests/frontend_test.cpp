#include <QString>
#include <QtWidgets/QtWidgets>
#include <QtTest/QtTest>
#include "core/communication.h"

class Frontend_Test : public QObject
{
    Q_OBJECT

public:
    Frontend_Test();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testCase1();
    void testCase2();
    void testCase3();
};

Frontend_Test::Frontend_Test()
{
}

void Frontend_Test::initTestCase()
{
}

void Frontend_Test::cleanupTestCase()
{
}

void Frontend_Test::testCase1()
{
    QString str = "Hello";
    QCOMPARE(str.toUpper(), QString("HELLO"));
}

void Frontend_Test::testCase2()
{
    QString str = "Hello";
    QVERIFY(str.toUpper() == "HELLO");
}

void Frontend_Test::testCase3()
{
    Communication* comm = new Communication();
    QVERIFY(comm->send_data() == "test");
}

QTEST_MAIN(Frontend_Test)
#include "frontend_test.moc"
