#include "droneconnection_integrationtest.h"


Droneconnection_IntegrationTest::Droneconnection_IntegrationTest()
{

}


void Droneconnection_IntegrationTest::initTestCase()
{
    count = 0;
    sim = new SimulatorWrapper();
    sim->startSimulator();



    drone = new DroneModule(6330, 5502,QString("127.0.0.1"), QString("127.0.0.1"),QString("127.0.0.1"), QString("rtp://127.0.0.1:5000"),  0.0001);
    m = new Mediator();

    drone->setMediator(m);
    drone->moveToThread(&th);
    th.start();
}

void Droneconnection_IntegrationTest::cleanupTestCase()
{
    QTest::qWait(500);
    th.quit();
    th.wait();
    QTest::qWait(500);
    delete drone;
    delete m;

    sim->stopSimulator();
    QTest::qWait(500);
    delete sim;
}


void Droneconnection_IntegrationTest::testDroneConnection()
{


    DroneConnection* connection = drone->getDroneConnection();

    connect(connection, SIGNAL(droneResponse(QString)), this, SLOT(onDroneResponse(QString)));


    drone->requestStatus();

    QTest::qWait(1000);

    QVERIFY(count > 0);
    qDebug() << "Simulator responds to query and response is received";


}

void Droneconnection_IntegrationTest::onDroneResponse(QString string)
{
    count++;
}
