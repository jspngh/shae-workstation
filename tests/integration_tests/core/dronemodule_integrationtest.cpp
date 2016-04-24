#include "dronemodule_integrationtest.h"

Dronemodule_IntegrationTest::Dronemodule_IntegrationTest()
{

}


void Dronemodule_IntegrationTest::init()
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
    m = controller->getMediator();

    QList<QGeoCoordinate> *waypointList = new QList<QGeoCoordinate>();
    waypointList->push_back(QGeoCoordinate(1.0, 1.0));
    waypointList->push_back(QGeoCoordinate(2.0, 2.0));
    drone->setWaypoints(waypointList);
}

void Dronemodule_IntegrationTest::cleanup()
{
    sim->stopSimulator();
    QTest::qWait(5000);
    delete sim;
    QTest::qWait(5000);
    delete controller;
}


void Dronemodule_IntegrationTest::testNavigationMessages()
{
    qDebug() << "Sending waypoints... ";

    drone->sendWaypoints();
    QTest::qWait(300);
    qDebug() << "Sending start... ";
    drone->startFlight();
    qDebug() << "Waiting for simulator to start flying, this takes some time... ";
    QTest::qWait(30000);
    qDebug() << "Sending stop... ";
    drone->stopFlight();
    QTest::qWait(300);
    qDebug() << "Sending emergency... ";
    drone->emergencyLanding();
    QTest::qWait(300);

    QList<QString> check = QList<QString>();
    check.push_back("workstation_config");
    check.push_back("path");
    check.push_back("start");
    check.push_back("stop");
    check.push_back("emergency");


    qDebug() << "Checking if simulator has received all these messages in correct order... ";

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
    qDebug() << "All messages received in right order ";


}

void Dronemodule_IntegrationTest::testStatusMessages()
{
    qDebug() << "requesting all status fields of drone... ";

    DroneConnection *connection = drone->getDroneConnection();

    connect(connection, SIGNAL(droneResponse(QString)), this, SLOT(onDroneResponse(QString)));

    drone->requestStatus();
    QTest::qWait(500);

    QList<QString> check = QList<QString>();
    check.push_back("workstation_config");
    check.push_back("all_statuses");

    qDebug() << "Checking if simulator has received the correct message... ";

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
    qDebug() << "Correct message was received by simulator ";


    QTest::qWait(2000);
    QVERIFY(count > 0);
    qDebug() << "Answer from simulator was received ";

}

void Dronemodule_IntegrationTest::testSettingsMessages()
{
    qDebug() << "trying some settings messages... ";

    DroneConnection *connection = drone->getDroneConnection();

    connect(connection, SIGNAL(droneResponse(QString)), this, SLOT(onDroneResponse(QString)));
    QList<RequestedDroneSetting> settings = QList<RequestedDroneSetting>();
    QList<int> values = QList<int>();

    settings.push_back(Height_To_Set);
    settings.push_back(Speed_To_Set);
    settings.push_back(Camera_Angle_To_Set);
    settings.push_back(FPS_To_Set);
    settings.push_back(Resolution_To_Set);

    values.push_back(3);
    values.push_back(4);
    values.push_back(70);
    values.push_back(30);
    values.push_back(720);


    drone->setSettings(settings, values);
    QTest::qWait(500);

    qDebug() << "Checking if simulator has received the correct message... ";

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
        QVERIFY(json["message_type"].toString() == "settings");
        QJsonArray array = json["message"].toArray();
        for (QJsonValue value : array) {
            QJsonObject obj = value.toObject();
            if (obj["key"].toString() == "height")
                QVERIFY(obj["value"].toInt() == 3);
            if (obj["key"].toString() == "speed")
                QVERIFY(obj["value"].toInt() == 4);
            if (obj["key"].toString() == "camera_angle")
                QVERIFY(obj["value"].toInt() == 70);
            if (obj["key"].toString() == "fps")
                QVERIFY(obj["value"].toInt() == 30);
            if (obj["key"].toString() == "resolution")
                QVERIFY(obj["value"].toInt() == 720);
        }
        j++;

    }
    qDebug() << "Correct message was received by simulator ";


    QTest::qWait(1000);
}

void Dronemodule_IntegrationTest::onDroneResponse(QString string)
{
    count++;
}
