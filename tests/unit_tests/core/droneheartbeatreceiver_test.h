#ifndef DRONEHEARTBEATRECEIVER_TEST_H
#define DRONEHEARTBEATRECEIVER_TEST_H
#include <QtTest>
#include "communication/droneheartbeatreceiver.h"

class DroneHeartbeatReceiver_Test : public QObject
{
    Q_OBJECT
public:
    explicit DroneHeartbeatReceiver_Test(QObject *parent = 0);

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testConstructorDestructor();
    void testSetandGet();
    void testReceiveHeartbeat();
private:
    void onDroneHeartbeatReceived();
    int count;
};

#endif // DRONEHEARTBEATRECEIVER_TEST_H
