#ifndef CONTROLLER_TEST_H
#define CONTROLLER_TEST_H

#include <QTest>
#include <core/controller.h>

class Controller_Test: public QObject
{
    Q_OBJECT

public:
    Controller_Test();


private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testConstructor();
    void testInitWorkstationIp();
    void testInitBroadcastIp();
    void testUdpSockets();

};

#endif // CONTROLLER_TEST_H


