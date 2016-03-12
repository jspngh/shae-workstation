#ifndef JSON_MESSAGES_TEST_H
#define JSON_MESSAGES_TEST_H
#include <QString>
#include <QtWidgets/QtWidgets>
#include <QtTest/QtTest>

class Json_Messages_Test: public QObject
{
    Q_OBJECT

public:
    Json_Messages_Test();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
};

#endif // JSON_MESSAGES_TEST_H
