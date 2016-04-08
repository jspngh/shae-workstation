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
//    QString program = "python";
//    QStringList arguments;
//    qDebug() << "opening simulator";
//    arguments << "../../../drone/simulator/src/simulator.py";
//    QProcess* simulatorProcess = new QProcess(this);
//    qDebug() << "simulator opened";
//    simulatorProcess->start(program, arguments);
//    QThread::sleep(5);


    DroneModule* drone = new DroneModule(6330, 5502,QString("127.0.0.1"), QString("127.0.0.1"),QString("127.0.0.1"), QString("rtp://127.0.0.1:5000"),  0.0001);
    Mediator* m = new Mediator();

    drone->setMediator(m);
    QThread th;
    drone->moveToThread(&th);
    th.start();


//    DroneHeartBeatReceiver* receiver = new DroneHeartBeatReceiver("127.0.0.1");
//    connect(receiver, &DroneHeartBeatReceiver::droneHeartBeat, this, &DroneHeartbeat_IntegrationTest::onDroneHeartbeatReceived);

    DroneHeartBeatReceiver* receiver = drone->getHeartbeatReceiver();
    connect(receiver, SIGNAL(droneHeartBeat(QString)), this, SLOT(onDroneHeartbeatReceived(QString)));



    //drone->setWorkstationConfiguration("127.0.0.1", receiver->getWorkstationHeartbeatPort());

    QTest::qWait(5000);
    QVERIFY(count > 0);




    //simulatorProcess->close();
    //delete simulatorProcess;

}

void DroneHeartbeat_IntegrationTest::onDroneHeartbeatReceived(QString string)
{
    count++;
}
