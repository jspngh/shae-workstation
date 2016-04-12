#include "dronemodule_integrationtest.h"

Dronemodule_IntegrationTest::Dronemodule_IntegrationTest()
{

}


void Dronemodule_IntegrationTest::initTestCase()
{
    sim = new SimulatorWrapper();
    sim->startSimulator();

    drone = new DroneModule(6330, 5502,QString("127.0.0.1"), QString("127.0.0.1"),QString("127.0.0.1"), QString("rtp://127.0.0.1:5000"),  0.0001);
    QList<QGeoCoordinate> *waypointList = new QList<QGeoCoordinate>();
    waypointList->push_back(QGeoCoordinate(1.0, 1.0));
    waypointList->push_back(QGeoCoordinate(2.0, 2.0));
    drone->setWaypoints(waypointList);


    m = new Mediator();

    drone->setMediator(m);

    drone->moveToThread(&th);
    th.start();

}

void Dronemodule_IntegrationTest::cleanupTestCase()
{
    QTest::qWait(1000);
    th.quit();
    th.wait();
    delete drone;
    delete m;
    sim->stopSimulator();
    delete sim;
}


void Dronemodule_IntegrationTest::testNavigationMessages()
{
    qDebug() << "Sending waypoints... "<< endl;

    drone->sendWaypoints();
    QTest::qWait(500);
    qDebug() << "Sending start... "<< endl;
    drone->startFlight();
    qDebug() << "Waiting for simulator to start flying... "<< endl;
    QTest::qWait(30000);
    qDebug() << "Sending stop... "<< endl;
    drone->stopFlight();
    QTest::qWait(2000);
    qDebug() << "Sending emergency... "<< endl;
    drone->emergencyLanding();
    QTest::qWait(2000);

    QList<QString> check = QList<QString>();
    check.push_back("workstation_config");
    check.push_back("path");
    check.push_back("start");
    check.push_back("stop");
    check.push_back("emergency");


    qDebug() << "Checking if simulator has received all these messages in correct order... "<< endl;

    QByteArray output = sim->simulatorProcess->readAllStandardOutput();
    //qDebug() << "Simulator has the generated the following output, which we wil check for the right messages: "<< endl << output;
    int j = 0;
    int indexend = 0;
    while ((j = output.indexOf("{\n", indexend)) != -1) {
        //get index of first opening {
        //get index of closing }
        int indexstart = j;
        //qDebug() << "Start parse at position " << j;
        int j = output.indexOf("\n}\n\n", indexstart);
        //qDebug() << "Stop parse at position " << j;
        indexend = j + 2 ;

        //then we got indexes of a json message that can be analyzed


        QByteArray jsonbits = output.mid(indexstart, indexend - indexstart).simplified();
        qDebug() << "Simulator has received this message: " << jsonbits;
        QJsonDocument jsondoc = QJsonDocument::fromJson(jsonbits);
        QJsonObject json = jsondoc.object();
        //qDebug() << json["message"] << endl;
        QVERIFY(json["message"].toString() == check.front());
        check.pop_front();




        //qDebug() << "Found \" \n}\n\n \" at index position " << j << endl;
        j++;

    }
    qDebug() << "All messages received in right order "<< endl;


}

void Dronemodule_IntegrationTest::testStatusMessages()
{

}

void Dronemodule_IntegrationTest::testSettingsMessages()
{

}
