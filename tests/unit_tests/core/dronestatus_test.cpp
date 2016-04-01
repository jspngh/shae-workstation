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
    QVERIFY( status.getBatteryLevel() == -1.0);
    QVERIFY( status.getCameraAngle() == -1);
    QVERIFY( status.getDroneState() == -1);
    QVERIFY( status.getFps() == -1);
    QVERIFY( status.getHeartbeat() == false);
    QVERIFY( status.getHeight() == -1);
    QVERIFY( status.getManufacturer() == "");
    QVERIFY( status.getType() == "");
    QVERIFY( status.getOrientation() == -1);
    QVERIFY( status.getResolution() == -1);
    QVERIFY( status.getSelectedHeight() == -1);
    QVERIFY( status.getSelectedSpeed() == -1);
    QVERIFY( status.getSpeed() == -1);
}

void DroneStatus_Test::testConstructor()
{
    QDateTime timestampDrone = QDateTime.currentDateTime();
    QDateTime timestampReceiveWorkstation = QDateTime.currentDateTime();
    QGeoCoordinate location = QGeoCoordinate(1.0);
    double orientation = 20.0;
    double cameraAngle = 15.0;
    double speed = 2.0;
    double batteryLevel = 50.4;
    int droneState = 1;

    DroneStatus status = DroneStatus(timestampDrone, timestampReceiveWorkstation,
                                     location, orientation, cameraAngle, speed,
                                     batteryLevel, droneState);

    QVERIFY( status.getBatteryLevel() == batteryLevel);
    QVERIFY( status.getCameraAngle() == cameraAngle);
    QVERIFY( status.getDroneState() == droneState);
    QVERIFY( status.getHeartbeat() == false);
    QVERIFY( status.getHeight() == -1);
    QVERIFY( status.getManufacturer() == "");
    QVERIFY( status.getType() == "");
    QVERIFY( status.getOrientation() == -1);
    QVERIFY( status.getResolution() == -1);
    QVERIFY( status.getSelectedHeight() == -1);
    QVERIFY( status.getSelectedSpeed() == -1);
    QVERIFY( status.getSpeed() == -1);
}


void DroneStatus_Test::testLongConstructor()
{

}

void DroneStatus_Test::testCopyConstructor()
{

}

void DroneStatus_Test::testFromJsonStringAllSet()
{

}


void DroneStatus_Test::testFromJsonStringNoneSet()
{

}

void DroneStatus_Test::testParseExceptionNotJson()
{

}

void DroneStatus_Test::testParseExceptionNotStatus()
{

}


//Test getters and setters
