#include <unistd.h>

#include "json_messages_test.h"

Json_Messages_Test::Json_Messages_Test()
{

}
void Json_Messages_Test::initTestCase()
{
    QUuid droneId = QUuid::createUuid();
    drone = new Drone(droneId, 45836, "127.0.0.1", 0.0001);
    std::list<QGeoCoordinate> waypointList = std::list<QGeoCoordinate>();
    waypointList.push_back(QGeoCoordinate(1.0,1.0));
    waypointList.push_back(QGeoCoordinate(2.0,2.0));
    drone->setWaypoints(waypointList);
}

void Json_Messages_Test::cleanupTestCase()
{
    usleep(10000);
}

void Json_Messages_Test::testNavigationMessages()
{
    //send the messages, but keep them in code.
    QJsonDocument doc1 = drone->emergencyLanding();
    QJsonDocument doc2 = drone->sendWaypoints();
    QJsonDocument doc3 = drone->startFlight();
    QJsonDocument doc4 = drone->stopFlight();

    QJsonObject json1 = doc1.object();
    QJsonObject json2 = doc2.object();
    QJsonObject json3 = doc3.object();
    QJsonObject json4 = doc4.object();

    //compare extracted fields to required fields
    QVERIFY( json1["MessageType"] == "navigation" );
    QVERIFY( json2["MessageType"] == "navigation" );
    QVERIFY( json3["MessageType"] == "navigation" );
    QVERIFY( json4["MessageType"] == "navigation" );

    QVERIFY( json1["Message"] == "emergency" );
    QVERIFY( json2["Message"] == "path" );
    QVERIFY( json3["Message"] == "start" );
    QVERIFY( json4["Message"] == "stop" );

    QJsonArray waypoints = json2["Waypoints"].toArray();
    QVERIFY( waypoints.at(0).toObject()["Order"] == 1 );
    QVERIFY( waypoints.at(1).toObject()["Order"] == 2 );

    QJsonObject waypoint1 = waypoints.at(0).toObject()["Location"].toObject();
    QJsonObject waypoint2 = waypoints.at(1).toObject()["Location"].toObject();

    QVERIFY(waypoint1["Latitude"].toDouble() == 1.0);
    QVERIFY(waypoint1["Longitude"].toDouble() == 1.0);
    QVERIFY(waypoint2["Latitude"].toDouble() == 2.0);
    QVERIFY(waypoint2["Longitude"].toDouble() == 2.0);
}

void Json_Messages_Test::testStatusMessages()
{
    std::list<DroneStatus> list = std::list<DroneStatus>();
    list.push_back(Battery_Level);
    list.push_back(Location);
    list.push_back(Drone_Type);
    list.push_back(Waypoint_Reached);

    QJsonDocument jsondoc = drone->requestStatuses(list);
    QJsonObject json = jsondoc.object();

    QVERIFY( json["MessageType"] == "status" );
    QJsonArray message = json["Message"].toArray();
    QVERIFY( message.at(0).toObject()["Key"] == "battery_level" );
    QVERIFY( message.at(1).toObject()["Key"] == "current_location" );
    QVERIFY( message.at(2).toObject()["Key"] == "drone_type" );
    QVERIFY( message.at(3).toObject()["Key"] == "waypoint_reached" );

    //Also test if just 1 status is sent
    jsondoc = drone->requestStatus(Location);
    json = jsondoc.object();
    QVERIFY( json["MessageType"] == "status" );
    message = json["Message"].toArray();
    QVERIFY( message.at(0).toObject()["Key"] == "current_location" );
}

void Json_Messages_Test::testSettingsMessages()
{
    std::list<DroneSetting> settingList = std::list<DroneSetting>();
    settingList.push_back(Speed);
    settingList.push_back(Height);
    settingList.push_back(Camera_Angle);
    settingList.push_back(Resolution);
    settingList.push_back(FPS);

    std::list<int> valueList = std::list<int>();
    valueList.push_back(3);
    valueList.push_back(4);
    valueList.push_back(60);
    valueList.push_back(720);
    valueList.push_back(30);

    QJsonDocument jsondoc = drone->setSettings(settingList, valueList);
    QJsonObject json = jsondoc.object();

    QVERIFY( json["MessageType"] == "settings" );
    QJsonArray message = json["Message"].toArray();
    QVERIFY( message.at(0).toObject()["Key"] == "speed" );
    QVERIFY( message.at(1).toObject()["Key"] == "height" );
    QVERIFY( message.at(2).toObject()["Key"] == "camera_angle" );
    QVERIFY( message.at(3).toObject()["Key"] == "resolution" );
    QVERIFY( message.at(4).toObject()["Key"] == "fps" );
    QVERIFY( message.at(0).toObject()["Value"].toInt() == 3);
    QVERIFY( message.at(1).toObject()["Value"].toInt() == 4 );
    QVERIFY( message.at(2).toObject()["Value"].toInt() == 60 );
    QVERIFY( message.at(3).toObject()["Value"].toInt() == 720 );
    QVERIFY( message.at(4).toObject()["Value"].toInt() == 30 );

    //Also test if just 1 status is sent
    jsondoc = drone->setSetting(FPS,60);
    json = jsondoc.object();
    QVERIFY( json["MessageType"] == "settings" );
    message = json["Message"].toArray();
    QVERIFY( message.at(0).toObject()["Key"] == "fps" );
    QVERIFY( message.at(0).toObject()["Value"].toInt() == 60 );
}


