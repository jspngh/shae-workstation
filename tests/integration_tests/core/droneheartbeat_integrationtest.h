#ifndef DRONEHEARTBEAT_INTEGRATIONTEST_H
#define DRONEHEARTBEAT_INTEGRATIONTEST_H
#include <QtTest>

class DroneHeartbeat_IntegrationTest : public QObject
{
    Q_OBJECT
public:
    DroneHeartbeat_IntegrationTest();

public slots:
    void onDroneHeartbeatReceived();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testReceiveHeartbeat();


private:
    int count;


};

#endif // DRONEHEARTBEAT_INTEGRATIONTEST_H
