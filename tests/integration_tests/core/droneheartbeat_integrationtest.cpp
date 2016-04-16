#include "droneheartbeat_integrationtest.h"


DroneHeartbeat_IntegrationTest::DroneHeartbeat_IntegrationTest()
{

}

void DroneHeartbeat_IntegrationTest::initTestCase()
{
    count = 0;
    simulator = new SimulatorWrapper();
    simulator->startSimulator();

    drone = new DroneModule(6330, 5502, QString("127.0.0.1"), QString("127.0.0.1"), QString("127.0.0.1"), QString("rtp://127.0.0.1:5000"),  0.0001);
    m = new Mediator();

    drone->setMediator(m);
    drone->moveToThread(&th);
    th.start();

}

void DroneHeartbeat_IntegrationTest::cleanupTestCase()
{
    QTest::qWait(500);
    th.quit();
    th.wait();
    QTest::qWait(500);
    delete drone;
    delete m;


    simulator->stopSimulator();
    QTest::qWait(500);
    delete simulator;
    QTest::qWait(5000);
}


void DroneHeartbeat_IntegrationTest::testReceiveHeartbeat()
{


    DroneHeartBeatReceiver *receiver = drone->getHeartbeatReceiver();
    connect(receiver, SIGNAL(droneHeartBeat(QString)), this, SLOT(onDroneHeartbeatReceived(QString)));





    QTest::qWait(5000);
    QVERIFY(count > 0);
    qDebug() << "Heartbeats get received";


}

void DroneHeartbeat_IntegrationTest::onDroneHeartbeatReceived(QString string)
{
    count++;
}
