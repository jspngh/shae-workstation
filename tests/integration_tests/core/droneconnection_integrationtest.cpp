#include "droneconnection_integrationtest.h"
#include "communication/dronemodule.h"

Droneconnection_IntegrationTest::Droneconnection_IntegrationTest()
{

}


void Droneconnection_IntegrationTest::initTestCase()
{
    count = 0;
}

void Droneconnection_IntegrationTest::cleanupTestCase()
{

}


void Droneconnection_IntegrationTest::testDroneConnection()
{
    SimulatorWrapper* sim = new SimulatorWrapper();
    sim->startSimulator();



    DroneModule* drone = new DroneModule(6330, 5502,QString("127.0.0.1"), QString("127.0.0.1"),QString("127.0.0.1"), QString("rtp://127.0.0.1:5000"),  0.0001);
    Mediator* m = new Mediator();

    drone->setMediator(m);
    QThread th;
    drone->moveToThread(&th);
    th.start();

    DroneConnection* connection = drone->getDroneConnection();

    connect(connection, SIGNAL(droneResponse(QString)), this, SLOT(onDroneResponse(QString)));


    drone->requestStatus();

    QTest::qWait(1000);

    QVERIFY(count > 0);


    delete drone;
    delete m;



    sim->stopSimulator();
    delete sim;

}

void Droneconnection_IntegrationTest::onDroneResponse(QString string)
{
    count++;
}
