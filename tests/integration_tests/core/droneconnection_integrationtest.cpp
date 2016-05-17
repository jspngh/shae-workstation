#include "droneconnection_integrationtest.h"


Droneconnection_IntegrationTest::Droneconnection_IntegrationTest()
{

}


void Droneconnection_IntegrationTest::initTestCase()
{
    count = 0;
    sim = new SimulatorWrapper();
    sim->startSimulator();

    MainWindow w;
    controller =  new Controller(&w);
    controller->init();

    // wait until a drone is connected to the controller
    // the controller needs to wait until the drone sends a hello message, indicating that it is ready
    while(controller->numDronesConnected() < 1) {
        qDebug() << "wait until a drone is connected to the controller";
        QTest::qWait(1000 * 5);
    }

    drone = (*(controller->getDrones()))[0];
    drone->initHeartbeat();
    m = controller->getMediator();
}

void Droneconnection_IntegrationTest::cleanupTestCase()
{
    sim->stopSimulator();
    QTest::qWait(500);
    delete sim;
    QTest::qWait(5000);
    delete controller;
}


void Droneconnection_IntegrationTest::testDroneConnection()
{


    DroneConnection *connection = drone->getDroneConnection();

    connect(connection, SIGNAL(droneResponse(QString)), this, SLOT(onDroneResponse(QString)));

    drone->requestStatus();

    QTest::qWait(2000);

    QVERIFY(count > 0);
    qDebug() << "Simulator responds to query and response is received";


}

void Droneconnection_IntegrationTest::onDroneResponse(QString string)
{
    count++;
}
