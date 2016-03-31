#ifndef JSON_MESSAGES_TEST_H
#define JSON_MESSAGES_TEST_H
#include <QString>
#include <QUuid>
#include <QtWidgets/QtWidgets>
#include <QtTest/QtTest>
#include "communication/dronemodule.h"


class Json_Messages_Test: public QObject
{
    Q_OBJECT

public:
    Json_Messages_Test();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testNavigationMessages();
    void testStatusMessages();
    void testSettingsMessages();

private:
    DroneModule *drone;
};

#endif // JSON_MESSAGES_TEST_H
