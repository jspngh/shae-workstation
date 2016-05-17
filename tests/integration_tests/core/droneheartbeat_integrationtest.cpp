#include "droneheartbeat_integrationtest.h"


DroneHeartbeat_IntegrationTest::DroneHeartbeat_IntegrationTest()
{

}

void DroneHeartbeat_IntegrationTest::initTestCase()
{
    count = 0;
    simulator = new SimulatorWrapper();
    simulator->startSimulator();

    MainWindow w;
    controller =  new Controller(&w);
    controller->init();

    // wait until a drone is connected to the controller
    // the controller needs to wait until the drone sends a hello message, indicating that it is ready
    while (controller->numDronesConnected() < 1) {
        qDebug() << "wait until a drone is connected to the controller";
        QTest::qWait(1000 * 5);
    }

    drone = (*(controller->getDrones()))[0];
    drone->initHeartbeat();
    m = controller->getMediator();
}

void DroneHeartbeat_IntegrationTest::cleanupTestCase()
{
    simulator->stopSimulator();
    QTest::qWait(500);
    delete simulator;
    QTest::qWait(5000);
    delete controller;
}


void DroneHeartbeat_IntegrationTest::testReceiveHeartbeat()
{
    QList<QGeoCoordinate> *list = new QList<QGeoCoordinate>();
    list->append(drone->getLastReceivedDroneStatus().getCurrentLocation());
    list->append(drone->getLastReceivedDroneStatus().getCurrentLocation());
    list->append(drone->getLastReceivedDroneStatus().getCurrentLocation());
    drone->setWaypoints(list);
    drone->sendWaypoints();
    drone->startFlight();
    qDebug() << "drone is flying...";
    QTest::qWait(15000);

    DroneHeartBeatReceiver *receiver = drone->getHeartbeatReceiver();
    connect(receiver, SIGNAL(droneHeartBeat(QString)), this, SLOT(onDroneHeartbeatReceived(QString)));

    QTest::qWait(10000);
    QVERIFY(count > 0);
    qDebug() << "Heartbeats get received";
}

void DroneHeartbeat_IntegrationTest::onDroneHeartbeatReceived(QString string)
{
    count++;
}
