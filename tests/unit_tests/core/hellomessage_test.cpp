#include "hellomessage_test.h"

HelloMessage_Test::HelloMessage_Test()
{

}

void HelloMessage_Test::initTestCase()
{
    // nothing needs to be initialized
}

void HelloMessage_Test::cleanupTestCase()
{
    // nothing needs to be cleaned up
}

void HelloMessage_Test::parse_test()
{
    QString helloString = "{"
                              "\"message_type\": \"hello\","
                              "\"ip_drone\": \"10.1.1.10\","
                              "\"ip_controller\": \"10.1.1.1\","
                              "\"port_stream\": 22,"
                              "\"port_commands\": 23,"
                              "\"stream_file\": \"path\","
                              "\"vision_width\": 0.1"
                          "}";

    QByteArray helloBytes = helloString.toLocal8Bit();

    HelloMessage hello = HelloMessage::parse(helloBytes);

    QVERIFY(hello.getCommandsPort() == 23);
    QVERIFY(hello.getStreamPort() == 22);
    QVERIFY(hello.getDroneIp() == "10.1.1.10");
    QVERIFY(hello.getControllerIp() == "10.1.1.1");
    QVERIFY(hello.getStreamFile() == "path");
    QVERIFY(hello.getVisionWidth() == 0.1);

}

void HelloMessage_Test::getters_test()
{
    QString ipDrone = QString("10.1.1.10");
    QString ipController = QString("10.1.1.1");
    int portStream = 33;
    int portCommands = 34;
    QString streamFile = QString("path_to_stream_file");
    double visionWidth = 0.1;

    HelloMessage *hello = new HelloMessage(ipDrone,
                                         streamFile,
                                         ipController,
                                         portCommands,
                                         portStream,
                                         visionWidth);

    QVERIFY(hello->getCommandsPort() == portCommands);
    QVERIFY(hello->getStreamPort() == portStream);
    QVERIFY(hello->getDroneIp() == ipDrone);
    QVERIFY(hello->getControllerIp() == ipController);
    QVERIFY(hello->getStreamFile() == streamFile);
    QVERIFY(hello->getVisionWidth() == visionWidth);

    delete hello;
}
