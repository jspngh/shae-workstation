#include "droneheartbeat_integrationtest.h"
#include "communication/dronemodule.h"
#include "core/controller.h"

DroneHeartbeat_IntegrationTest::DroneHeartbeat_IntegrationTest()
{

}

void DroneHeartbeat_IntegrationTest::initTestCase()
{
    count = 0;
}

void DroneHeartbeat_IntegrationTest::cleanupTestCase()
{

}


void DroneHeartbeat_IntegrationTest::testReceiveHeartbeat()
{
    SimulatorWrapper* simulator = new SimulatorWrapper();
    simulator->startSimulator();

    DroneModule* drone = new DroneModule(6330, 5502,QString("127.0.0.1"), QString("127.0.0.1"),QString("127.0.0.1"), QString("rtp://127.0.0.1:5000"),  0.0001);
    Mediator* m = new Mediator();

    drone->setMediator(m);
    QThread th;
    drone->moveToThread(&th);
    th.start();


    DroneHeartBeatReceiver* receiver = drone->getHeartbeatReceiver();
    connect(receiver, SIGNAL(droneHeartBeat(QString)), this, SLOT(onDroneHeartbeatReceived(QString)));





    QTest::qWait(5000);
    QVERIFY(count > 0);

    th.quit();
    th.wait();
    delete drone;
    delete m;


    simulator->stopSimulator();
    delete simulator;
}

void DroneHeartbeat_IntegrationTest::onDroneHeartbeatReceived(QString string)
{
    count++;
}
