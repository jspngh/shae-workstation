#include <unistd.h>

#include "json_messages_test.h"

Json_Messages_Test::Json_Messages_Test()
{

}
void Json_Messages_Test::initTestCase()
{
    drone = new DroneModule(6331, 5502, "127.0.0.1", "127.0.0.1", "127.0.0.1", "rtp://127.0.0.1:5000", 0.0001);
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
    QVERIFY(json1["message_type"] == QString("navigation"));
    QVERIFY(json2["message_type"] == QString("navigation"));
    QVERIFY(json3["message_type"] == QString("navigation"));
    QVERIFY(json4["message_type"] == QString("navigation"));

    QVERIFY(json1["message"] == QString("emergency"));
    QVERIFY(json2["message"] == QString("path"));
    QVERIFY(json3["message"] == QString("start"));
    QVERIFY(json4["message"] == QString("stop"));

    QJsonArray waypoints = json2["waypoints"].toArray();
    QVERIFY(waypoints.at(0).toObject()["order"] == 1);
    QVERIFY(waypoints.at(1).toObject()["order"] == 2);

    QJsonObject waypoint1 = waypoints.at(0).toObject()["location"].toObject();
    QJsonObject waypoint2 = waypoints.at(1).toObject()["location"].toObject();

    QVERIFY(waypoint1["latitude"].toDouble() == 1.0);
    QVERIFY(waypoint1["longitude"].toDouble() == 1.0);
    QVERIFY(waypoint2["latitude"].toDouble() == 2.0);
    QVERIFY(waypoint2["longitude"].toDouble() == 2.0);
}

void Json_Messages_Test::testStatusMessages()
{
    QList<RequestedDroneStatus> list = QList<RequestedDroneStatus>();
    list.push_back(Battery_Level);
    list.push_back(Location);
    list.push_back(Drone_Type);
    list.push_back(Waypoint_Order);
    list.push_back(Next_Waypoint);
    list.push_back(Next_Waypoints);
    list.push_back(Speed);
    list.push_back(Selected_Speed);
    list.push_back(Height);
    list.push_back(Selected_Height);
    list.push_back(Camera_Angle);
    list.push_back(FPS);
    list.push_back(Resolution);

    QJsonDocument jsondoc = drone->requestStatuses(list);
    usleep(1000);
    QJsonObject json = jsondoc.object();

    QVERIFY(json["message_type"] == QString("status"));
    QJsonArray message = json["message"].toArray();
    QVERIFY(message.at(0).toObject()["key"] == QString("battery_level"));
    QVERIFY(message.at(1).toObject()["key"] == QString("current_location"));
    QVERIFY(message.at(2).toObject()["key"] == QString("drone_type"));
    QVERIFY(message.at(3).toObject()["key"] == QString("waypoint_order"));
    QVERIFY(message.at(4).toObject()["key"] == QString("next_waypoint"));
    QVERIFY(message.at(5).toObject()["key"] == QString("next_waypoints"));
    QVERIFY(message.at(6).toObject()["key"] == QString("speed"));
    QVERIFY(message.at(7).toObject()["key"] == QString("selected_speed"));
    QVERIFY(message.at(8).toObject()["key"] == QString("height"));
    QVERIFY(message.at(9).toObject()["key"] == QString("selected_height"));
    QVERIFY(message.at(10).toObject()["key"] == QString("camera_angle"));
    QVERIFY(message.at(11).toObject()["key"] == QString("fps"));
    QVERIFY(message.at(12).toObject()["key"] == QString("resolution"));



    //Also test if just 1 status is sent
    jsondoc = drone->requestStatus(Location);
    usleep(1000);
    json = jsondoc.object();
    QVERIFY(json["message_type"] == QString("status"));
    message = json["message"].toArray();
    QVERIFY(message.at(0).toObject()["key"] == QString("current_location"));

    //Also test if all statusses are asked
    jsondoc = drone->requestStatus();
    usleep(1000);
    json = jsondoc.object();
    QVERIFY(json["message_type"] == QString("status"));
    QVERIFY(json["message"] == QString("all_statuses"));

    //Also test reqeustHeartbeat message
    jsondoc = drone->requestHeartbeat();
    usleep(1000);
    json = jsondoc.object();
    QVERIFY(json["message_type"] == QString("status"));
    QVERIFY(json["message"] == QString("heartbeat"));
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

    QVERIFY(json["message_type"] == QString("settings"));
    QJsonArray message = json["message"].toArray();
    QVERIFY(message.at(0).toObject()["key"] == QString("speed"));
    QVERIFY(message.at(1).toObject()["key"] == QString("height"));
    QVERIFY(message.at(2).toObject()["key"] == QString("camera_angle"));
    QVERIFY(message.at(3).toObject()["key"] == QString("resolution"));
    QVERIFY(message.at(4).toObject()["key"] == QString("fps"));
    QVERIFY(message.at(0).toObject()["value"].toInt() == 3);
    QVERIFY(message.at(1).toObject()["value"].toInt() == 4);
    QVERIFY(message.at(2).toObject()["value"].toInt() == 60);
    QVERIFY(message.at(3).toObject()["value"].toInt() == 720);
    QVERIFY(message.at(4).toObject()["value"].toInt() == 30);

    //Also test if just 1 status is sent
    jsondoc = drone->setSetting(FPS_To_Set, 60);
    usleep(1000);
    json = jsondoc.object();
    QVERIFY(json["message_type"] == QString("settings"));
    message = json["message"].toArray();
    QVERIFY(message.at(0).toObject()["key"] == QString("fps"));
    QVERIFY(message.at(0).toObject()["value"].toInt() == 60);

    //test setWorkstationConfiguration
    jsondoc = drone->setWorkstationConfiguration("127.0.0.1", 5555);
    usleep(1000);
    json = jsondoc.object();
    QVERIFY(json["message_type"] == QString("settings"));
    QVERIFY(json["message"] == QString("workstation_config"));
    QJsonObject config = json["configuration"].toObject();
    QVERIFY(config["ip_address"] == QString("127.0.0.1"));
    QVERIFY(config["port"] == QString::number(5555));

}
