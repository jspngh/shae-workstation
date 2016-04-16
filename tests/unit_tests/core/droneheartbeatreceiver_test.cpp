#include "droneheartbeatreceiver_test.h"
#include "models/drone.h"
#include "communication/dronemodule.h"

DroneHeartbeatReceiver_Test::DroneHeartbeatReceiver_Test(QObject *parent) : QObject(parent)
{

}

void DroneHeartbeatReceiver_Test::initTestCase()
{

}

void DroneHeartbeatReceiver_Test::cleanupTestCase()
{

}

void DroneHeartbeatReceiver_Test::testConstructorDestructor()
{
    DroneHeartBeatReceiver *receiver = new DroneHeartBeatReceiver("127.0.0.1");
    QVERIFY(receiver->getWorkstationHeartbeatPort() > 0);
    delete receiver;
}

void DroneHeartbeatReceiver_Test::testSetandGet()
{
    DroneHeartBeatReceiver *receiver = new DroneHeartBeatReceiver("127.0.0.1");

    receiver->setWorkstationHeartbeatPort(9000);
    QVERIFY(receiver->getWorkstationHeartbeatPort() == 9000);
    delete receiver;
}

//Moved to integration test
/*void DroneHeartbeatReceiver_Test::testReceiveHeartbeat()
{
//    QString program = "python";
//    QStringList arguments;
//    qDebug() << "opening simulator";
//    arguments << "../../../drone/simulator/src/simulator.py";
//    QProcess* simulatorProcess = new QProcess(this);
//    qDebug() << "simulator opened";
//    simulatorProcess->start(program, arguments);
//    QThread::sleep(5);


    DroneModule* drone = new DroneModule(6330, 5502, "127.0.0.1", QString("rtp://127.0.0.1:5000"),  0.0001);

    DroneHeartBeatReceiver* receiver = new DroneHeartBeatReceiver("127.0.0.1");
    connect(receiver, &DroneHeartBeatReceiver::droneHeartBeat, this, &DroneHeartbeatReceiver_Test::onDroneHeartbeatReceived);


    drone->setWorkstationConfiguration("127.0.0.1", receiver->getWorkstationHeartbeatPort());

    usleep(5000000);
    //QVERIFY(count > 0);




    //simulatorProcess->close();
    //delete simulatorProcess;

}

void DroneHeartbeatReceiver_Test::onDroneHeartbeatReceived()
{
    count++;
}*/
