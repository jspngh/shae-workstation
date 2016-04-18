#include "dronestatus_test.h"


DroneStatus_Test::DroneStatus_Test()
{

}

void DroneStatus_Test::initTestCase()
{

}

void DroneStatus_Test::cleanupTestCase()
{

}

void DroneStatus_Test::testDefaultConstructor()
{
    DroneStatus status = DroneStatus();
    QVERIFY(status.getBatteryLevel() == -1.0);
    QVERIFY(status.getCameraAngle() == -1);
    QVERIFY(status.getDroneState() == -1);
    QVERIFY(status.getFps() == -1);
    QVERIFY(status.getHeartbeat() == false);
    QVERIFY(status.getHeight() == -1);
    QVERIFY(status.getManufacturer() == "");
    QVERIFY(status.getType() == "");
    QVERIFY(status.getOrientation() == -1);
    QVERIFY(status.getResolution() == -1);
    QVERIFY(status.getSelectedHeight() == -1);
    QVERIFY(status.getSelectedSpeed() == -1);
    QVERIFY(status.getSpeed() == -1);
}

void DroneStatus_Test::testConstructor()
{
    QDateTime timestampDrone = QDateTime::currentDateTime();
    QDateTime timestampReceiveWorkstation = QDateTime::currentDateTime();
    QGeoCoordinate location = QGeoCoordinate(1.0, 1.0);
    double orientation = 20.0;
    double cameraAngle = 15.0;
    double speed = 2.0;
    double batteryLevel = 50.4;
    int droneState = 1;

    DroneStatus status = DroneStatus(timestampDrone, timestampReceiveWorkstation,
                                     location, orientation, cameraAngle, speed,
                                     batteryLevel, droneState);

    QVERIFY(status.getBatteryLevel() == batteryLevel);
    QVERIFY(status.getCameraAngle() == cameraAngle);
    QVERIFY(status.getDroneState() == droneState);
    QVERIFY(status.getHeartbeat() == false);
    QVERIFY(status.getHeight() == -1);
    QVERIFY(status.getManufacturer() == "");
    QVERIFY(status.getType() == "");
    QVERIFY(status.getOrientation() == orientation);
    QVERIFY(status.getResolution() == -1);
    QVERIFY(status.getSelectedHeight() == -1);
    QVERIFY(status.getSelectedSpeed() == -1);
    QVERIFY(status.getSpeed() == speed);
    QVERIFY(status.getCurrentLocation() == location);
    QVERIFY(status.getTimestampDrone() == timestampDrone);
    QVERIFY(status.getTimestampReceivedWorkstation() == timestampReceiveWorkstation);
}


void DroneStatus_Test::testLongConstructor()
{

    QDateTime timestampDrone = QDateTime::currentDateTime();
    QDateTime timestampReceiveWorkstation = QDateTime::currentDateTime();
    QGeoCoordinate location = QGeoCoordinate(1.0, 1.0);
    double orientation = 20.0;
    double cameraAngle = 15.0;
    double speed = 2.0;
    double selectedSpeed = 3.0;
    double height = 4.0;
    double selectedHeight = 4.2;
    double batteryLevel = 50.4;
    int fps = 30;
    int resolution = 720;
    bool heartbeat = false;
    QString manufacturer = "3dr";
    QString type = "solo";
    QGeoCoordinate nextWaypoint = QGeoCoordinate(0.0, 2.0);
    int previousWaypointOrder = 3;
    QList<QGeoCoordinate> nextWaypoints = QList<QGeoCoordinate>();
    nextWaypoints.push_back(QGeoCoordinate(0.0, 4.0));
    int droneState = 1;

    DroneStatus status = DroneStatus(timestampDrone, timestampReceiveWorkstation,
                                     location, orientation, cameraAngle, speed, selectedSpeed,
                                     height, selectedHeight,
                                     batteryLevel, fps, resolution, heartbeat, droneState,
                                     manufacturer, type, nextWaypoint, previousWaypointOrder, nextWaypoints);

    QVERIFY(status.getBatteryLevel() == batteryLevel);
    QVERIFY(status.getCameraAngle() == cameraAngle);
    QVERIFY(status.getDroneState() == droneState);
    QVERIFY(status.getHeartbeat() == heartbeat);
    QVERIFY(status.getHeight() == height);
    QVERIFY(status.getManufacturer() == manufacturer);
    QVERIFY(status.getType() == type);
    QVERIFY(status.getOrientation() == orientation);
    QVERIFY(status.getResolution() == resolution);
    QVERIFY(status.getSelectedHeight() == selectedHeight);
    QVERIFY(status.getSelectedSpeed() == selectedSpeed);
    QVERIFY(status.getTimestampDrone() == timestampDrone);
    QVERIFY(status.getTimestampReceivedWorkstation() == timestampReceiveWorkstation);
    QVERIFY(status.getCurrentLocation() == location);
    QVERIFY(status.getFps() == fps);
    QVERIFY(status.getManufacturer() == manufacturer);
    QVERIFY(status.getType() == type);
    QVERIFY(status.getNextWaypoint() == nextWaypoint);
    QVERIFY(status.getPreviousWaypointOrder() == previousWaypointOrder);
    QVERIFY(status.getNextWaypoints() == nextWaypoints);
    QVERIFY(status.getSpeed() == speed);


}

void DroneStatus_Test::testCopyConstructor()
{

    QDateTime timestampDrone = QDateTime::currentDateTime();
    QDateTime timestampReceiveWorkstation = QDateTime::currentDateTime();
    QGeoCoordinate location = QGeoCoordinate(1.0, 1.0);
    double orientation = 20.0;
    double cameraAngle = 15.0;
    double speed = 2.0;
    double selectedSpeed = 3.0;
    double height = 4.0;
    double selectedHeight = 4.2;
    double batteryLevel = 50.4;
    int fps = 30;
    int resolution = 720;
    bool heartbeat = false;
    QString manufacturer = "3dr";
    QString type = "solo";
    QGeoCoordinate nextWaypoint = QGeoCoordinate(0.0, 2.0);
    int previousWaypointOrder = 3;
    QList<QGeoCoordinate> nextWaypoints = QList<QGeoCoordinate>();
    nextWaypoints.push_back(QGeoCoordinate(0.0, 4.0));
    int droneState = 1;

    DroneStatus status = DroneStatus(timestampDrone, timestampReceiveWorkstation,
                                     location, orientation, cameraAngle, speed, selectedSpeed,
                                     height, selectedHeight,
                                     batteryLevel, fps, resolution, heartbeat, droneState,
                                     manufacturer, type, nextWaypoint, previousWaypointOrder, nextWaypoints);
    DroneStatus statusCopy = DroneStatus(status);

    QVERIFY(status.getBatteryLevel() == statusCopy.getBatteryLevel());
    QVERIFY(status.getCameraAngle() == statusCopy.getCameraAngle());
    QVERIFY(status.getDroneState() == statusCopy.getDroneState());
    QVERIFY(status.getHeartbeat() == statusCopy.getHeartbeat());
    QVERIFY(status.getHeight() == statusCopy.getHeight());
    QVERIFY(status.getManufacturer() == statusCopy.getManufacturer());
    QVERIFY(status.getType() == statusCopy.getType());
    QVERIFY(status.getOrientation() == statusCopy.getOrientation());
    QVERIFY(status.getResolution() == statusCopy.getResolution());
    QVERIFY(status.getSelectedHeight() == statusCopy.getSelectedHeight());
    QVERIFY(status.getSelectedSpeed() == statusCopy.getSelectedSpeed());
    QVERIFY(status.getTimestampDrone() == statusCopy.getTimestampDrone());
    QVERIFY(status.getTimestampReceivedWorkstation() == statusCopy.getTimestampReceivedWorkstation());
    QVERIFY(status.getCurrentLocation() == statusCopy.getCurrentLocation());
    QVERIFY(status.getFps() == statusCopy.getFps());
    QVERIFY(status.getType() == statusCopy.getType());
    QVERIFY(status.getNextWaypoint() == statusCopy.getNextWaypoint());
    QVERIFY(status.getPreviousWaypointOrder() == statusCopy.getPreviousWaypointOrder());
    QVERIFY(status.getNextWaypoints() == statusCopy.getNextWaypoints());
    QVERIFY(status.getSpeed() == statusCopy.getSpeed());

}

void DroneStatus_Test::testFromJsonStringAllSet()
{
    DroneStatus status;
    try {
        //TODO: create message containing all attributes
        status = DroneStatus::fromJsonString("{ \"message_type\": \"status\" ,"
                                             " \"message\": \"olaaa\" ,"
                                             " \"orientation\": 20.0 ,"
                                             " \"camera_angle\": 60.4 ,"
                                             " \"speed\": 3.0 ,"
                                             " \"selected_speed\": 4.0 ,"
                                             " \"height\": 2.0 ,"
                                             " \"selected_height\": 5.0 ,"
                                             " \"battery_level\": 53.8 ,"
                                             " \"drone_state\": 1 ,"
                                             " \"fps\": 20 ,"
                                             " \"heartbeat\": true ,"
                                             " \"resolution\": 720 ,"
                                             " \"current_location\": {"
                                             "  \"latitude\": 23.3245,"
                                             "  \"longitude\": 12.358959"
                                             " } ,"
                                             " \"drone_type\": {"
                                             " \"manufacturer\": \"3dr\","
                                             " \"model\": \"solo\""
                                             " } ,"
                                             " \"next_waypoint\": {"
                                             "  \"latitude\": 0.0,"
                                             "  \"longitude\": 1.0"
                                             " } ,"
                                             " \"next_waypoints\": [{"
                                             " \"latitude\": 0.0,"
                                             " \"longitude\": 1.0"
                                             " },"
                                             " {"
                                             " \"latitude\": 2.1,"
                                             " \"longitude\": 1.8"
                                             " }] ,"
                                             " \"waypoint_order\": 2 ,"
                                             " \"timestamp\": \"23032016214348009\" "
                                             "}");
    } catch (ParseException e) {
        qDebug() << e.what();
    }
    //TODO: verify all attributes
    QVERIFY(status.getOrientation() == 20.0);
    QVERIFY(status.getCameraAngle() == 60.4);
    QVERIFY(status.getSpeed() == 3.0);
    QVERIFY(status.getSelectedSpeed() == 4.0);
    QVERIFY(status.getHeight() == 2.0);
    QVERIFY(status.getSelectedHeight() == 5.0);
    QVERIFY(status.getBatteryLevel() == 53.8);

    QVERIFY(status.getDroneState() == 1);

    QVERIFY(status.getFps() == 20);
    QVERIFY(status.getHeartbeat() == true);

    QVERIFY(status.getManufacturer() == "3dr");
    QVERIFY(status.getType() == "solo");

    QVERIFY(status.getResolution() == 720);

    QVERIFY(status.getCurrentLocation() == QGeoCoordinate(23.3245, 12.358959));
    QVERIFY(status.getNextWaypoint() == QGeoCoordinate(0.0, 1.0));
    QList<QGeoCoordinate> next = QList<QGeoCoordinate>();
    next.push_back(QGeoCoordinate(0.0, 1.0));
    next.push_back(QGeoCoordinate(2.1, 1.8));
    for (QGeoCoordinate coor : status.getNextWaypoints()) {
        QVERIFY(coor == next.front());
        next.pop_front();
    }
    QVERIFY(status.getPreviousWaypointOrder() == 2);
    QVERIFY(status.getTimestampDrone() == QDateTime::fromString("23032016214348009", "ddMMyyyyHHmmsszzz"));
    QVERIFY(status.getTimestampReceivedWorkstation() > status.getTimestampDrone());




}


void DroneStatus_Test::testFromJsonStringNoneSet()
{
    DroneStatus status;
    try {
        status = DroneStatus::fromJsonString("{ \"message_type\": \"status\" , \"message\": \"olaaa\" }");
    } catch (ParseException e) {

    }
    QVERIFY(status.getBatteryLevel() == -1.0);
    QVERIFY(status.getCameraAngle() == -1);
    QVERIFY(status.getDroneState() == -1);
    QVERIFY(status.getFps() == -1);
    QVERIFY(status.getHeartbeat() == false);
    QVERIFY(status.getHeight() == -1);
    QVERIFY(status.getManufacturer() == "");
    QVERIFY(status.getType() == "");
    QVERIFY(status.getOrientation() == -1);
    QVERIFY(status.getResolution() == -1);
    QVERIFY(status.getSelectedHeight() == -1);
    QVERIFY(status.getSelectedSpeed() == -1);
    QVERIFY(status.getSpeed() == -1);

}

void DroneStatus_Test::testParseExceptionNotJson()
{
    int count = 0;
    try {
        DroneStatus status = DroneStatus::fromJsonString("This is not a Json string");
    } catch (ParseException e) {
        if (e.getError() == "Not a Json object")
            count++;
    }
    QVERIFY(count == 1);
}

void DroneStatus_Test::testParseExceptionNotStatus()
{
    int count = 0;
    try {
        DroneStatus status = DroneStatus::fromJsonString("{ \"message_type\": \"setting\" , \"message\": \"olaaa\" }");
    } catch (ParseException e) {
        if (e.getError() == "Not a status message")
            count++;
    }
    QVERIFY(count == 1);
}


void DroneStatus_Test::testSetters()
{
    DroneStatus status = DroneStatus();
    QDateTime timestampDrone = QDateTime::currentDateTime();
    QDateTime timestampReceiveWorkstation = QDateTime::currentDateTime();
    QGeoCoordinate location = QGeoCoordinate(1.0, 1.0);
    double orientation = 20.0;
    double cameraAngle = 15.0;
    double speed = 2.0;
    double selectedSpeed = 3.0;
    double height = 4.0;
    double selectedHeight = 4.2;
    double batteryLevel = 50.4;
    int fps = 30;
    int resolution = 720;
    bool heartbeat = false;
    QString manufacturer = "3dr";
    QString type = "solo";
    QGeoCoordinate nextWaypoint = QGeoCoordinate(0.0, 2.0);
    int previousWaypointOrder = 3;
    QList<QGeoCoordinate> nextWaypoints = QList<QGeoCoordinate>();
    nextWaypoints.push_back(QGeoCoordinate(0.0, 4.0));
    int droneState = 1;

    status.setBatteryLevel(batteryLevel);
    status.setCameraAngle(cameraAngle);
    status.setDroneState(droneState);
    status.setHeartbeat(heartbeat);
    status.setHeight(height);
    status.setManufacturer(manufacturer);
    status.setType(type);
    status.setOrientation(orientation);
    status.setResolution(resolution);
    status.setSelectedHeight(selectedHeight);
    status.setSelectedSpeed(selectedSpeed);
    status.setTimestampDrone(timestampDrone);
    status.setTimestampRecievedWorkstation(timestampReceiveWorkstation);
    status.setCurrentLocation(location);
    status.setFps(fps);
    status.setManufacturer(manufacturer);
    status.setType(type);
    status.setNextWaypoint(nextWaypoint);
    status.setPreviousWaypointOrder(previousWaypointOrder);
    status.setNextWaypoints(nextWaypoints);
    status.setSpeed(speed);


    QVERIFY(status.getSpeed() == speed);
    QVERIFY(status.getBatteryLevel() == batteryLevel);
    QVERIFY(status.getCameraAngle() == cameraAngle);
    QVERIFY(status.getDroneState() == droneState);
    QVERIFY(status.getHeartbeat() == heartbeat);
    QVERIFY(status.getHeight() == height);
    QVERIFY(status.getManufacturer() == manufacturer);
    QVERIFY(status.getType() == type);
    QVERIFY(status.getOrientation() == orientation);
    QVERIFY(status.getResolution() == resolution);
    QVERIFY(status.getSelectedHeight() == selectedHeight);
    QVERIFY(status.getSelectedSpeed() == selectedSpeed);
    QVERIFY(status.getTimestampDrone() == timestampDrone);
    QVERIFY(status.getTimestampReceivedWorkstation() == timestampReceiveWorkstation);
    QVERIFY(status.getCurrentLocation() == location);
    QVERIFY(status.getFps() == fps);
    QVERIFY(status.getManufacturer() == manufacturer);
    QVERIFY(status.getType() == type);
    QVERIFY(status.getNextWaypoint() == nextWaypoint);
    QVERIFY(status.getPreviousWaypointOrder() == previousWaypointOrder);
    QVERIFY(status.getNextWaypoints() == nextWaypoints);

}
