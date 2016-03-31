#include <unistd.h>

#include "json_messages_test.h"

Json_Messages_Test::Json_Messages_Test()
{

}
void Json_Messages_Test::initTestCase()
{
    drone = new DroneModule(6331, 5502, "127.0.0.1", "rtp://127.0.0.1:5000", 0.0001);
    QList<QGeoCoordinate> *waypointList = new QList<QGeoCoordinate>();
    waypointList->push_back(QGeoCoordinate(1.0, 1.0));
    waypointList->push_back(QGeoCoordinate(2.0, 2.0));
    drone->setWaypoints(waypointList);
}

void Json_Messages_Test::cleanupTestCase()
{

}

void Json_Messages_Test::testNavigationMessages()
{
    //send the messages, but keep them in code.

    QJsonDocument doc1 = drone->emergencyLanding();
    usleep(1000);
    QJsonDocument doc2 = drone->sendWaypoints();
    usleep(1000);
    QJsonDocument doc3 = drone->startFlight();
    usleep(1000);
    QJsonDocument doc4 = drone->stopFlight();
    usleep(1000);

    QJsonObject json1 = doc1.object();
    QJsonObject json2 = doc2.object();
    QJsonObject json3 = doc3.object();
    QJsonObject json4 = doc4.object();

    //compare extracted fields to required fields
    QVERIFY(json1["MessageType"] == QString("navigation"));
    QVERIFY(json2["MessageType"] == QString("navigation"));
    QVERIFY(json3["MessageType"] == QString("navigation"));
    QVERIFY(json4["MessageType"] == QString("navigation"));

    QVERIFY(json1["Message"] == QString("emergency"));
    QVERIFY(json2["Message"] == QString("path"));
    QVERIFY(json3["Message"] == QString("start"));
    QVERIFY(json4["Message"] == QString("stop"));

    QJsonArray waypoints = json2["Waypoints"].toArray();
    QVERIFY(waypoints.at(0).toObject()["Order"] == 1);
    QVERIFY(waypoints.at(1).toObject()["Order"] == 2);

    QJsonObject waypoint1 = waypoints.at(0).toObject()["Location"].toObject();
    QJsonObject waypoint2 = waypoints.at(1).toObject()["Location"].toObject();

    QVERIFY(waypoint1["Latitude"].toDouble() == 1.0);
    QVERIFY(waypoint1["Longitude"].toDouble() == 1.0);
    QVERIFY(waypoint2["Latitude"].toDouble() == 2.0);
    QVERIFY(waypoint2["Longitude"].toDouble() == 2.0);
}

void Json_Messages_Test::testStatusMessages()
{
    QList<RequestedDroneStatus> list = QList<RequestedDroneStatus>();
    list.push_back(Battery_Level);
    list.push_back(Location);
    list.push_back(Drone_Type);
    list.push_back(Waypoint_Reached);

    QJsonDocument jsondoc = drone->requestStatuses(list);
    usleep(1000);
    QJsonObject json = jsondoc.object();

    QVERIFY(json["MessageType"] == QString("status"));
    QJsonArray message = json["Message"].toArray();
    QVERIFY(message.at(0).toObject()["Key"] == QString("battery_level"));
    QVERIFY(message.at(1).toObject()["Key"] == QString("current_location"));
    QVERIFY(message.at(2).toObject()["Key"] == QString("drone_type"));
    QVERIFY(message.at(3).toObject()["Key"] == QString("waypoint_reached"));

    //Also test if just 1 status is sent
    jsondoc = drone->requestStatus(Location);
    usleep(1000);
    json = jsondoc.object();
    QVERIFY(json["MessageType"] == QString("status"));
    message = json["Message"].toArray();
    QVERIFY(message.at(0).toObject()["Key"] == QString("current_location"));
}

void Json_Messages_Test::testSettingsMessages()
{
    QList<RequestedDroneSetting> settingList = QList<RequestedDroneSetting>();
    settingList.push_back(Speed_To_Set);
    settingList.push_back(Height_To_Set);
    settingList.push_back(Camera_Angle_To_Set);
    settingList.push_back(Resolution_To_Set);
    settingList.push_back(FPS_To_Set);

    QList<int> valueList = QList<int>();
    valueList.push_back(3);
    valueList.push_back(4);
    valueList.push_back(60);
    valueList.push_back(720);
    valueList.push_back(30);

    QJsonDocument jsondoc = drone->setSettings(settingList, valueList);
    usleep(1000);
    QJsonObject json = jsondoc.object();

    QVERIFY(json["MessageType"] == QString("settings"));
    QJsonArray message = json["Message"].toArray();
    QVERIFY(message.at(0).toObject()["Key"] == QString("speed"));
    QVERIFY(message.at(1).toObject()["Key"] == QString("height"));
    QVERIFY(message.at(2).toObject()["Key"] == QString("camera_angle"));
    QVERIFY(message.at(3).toObject()["Key"] == QString("resolution"));
    QVERIFY(message.at(4).toObject()["Key"] == QString("fps"));
    QVERIFY(message.at(0).toObject()["Value"].toInt() == 3);
    QVERIFY(message.at(1).toObject()["Value"].toInt() == 4);
    QVERIFY(message.at(2).toObject()["Value"].toInt() == 60);
    QVERIFY(message.at(3).toObject()["Value"].toInt() == 720);
    QVERIFY(message.at(4).toObject()["Value"].toInt() == 30);

    //Also test if just 1 status is sent
    jsondoc = drone->setSetting(FPS_To_Set, 60);
    usleep(1000);
    json = jsondoc.object();
    QVERIFY(json["MessageType"] == QString("settings"));
    message = json["Message"].toArray();
    QVERIFY(message.at(0).toObject()["Key"] == QString("fps"));
    QVERIFY(message.at(0).toObject()["Value"].toInt() == 60);

}
