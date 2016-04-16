#include "streamconnection_test.h"

StreamConnection_Test::StreamConnection_Test()
{

}

void StreamConnection_Test::initTestCase()
{

}

void StreamConnection_Test::cleanUpTestCase()
{

}

void StreamConnection_Test::testConstructor()
{
    StreamConnection *c = new StreamConnection("127.0.0.1", 30000);
    QVERIFY(c->getDroneIpAddress() == "127.0.0.1");
    QVERIFY(c->getStreamPort() == 30000);
    QVERIFY(c->getGetStream() == true);
    delete c;
}

void StreamConnection_Test::testDestructor()
{
    StreamConnection *c = new StreamConnection("127.0.0.1", 30000);
    delete c;
}

void StreamConnection_Test::testStopConnection()
{
    StreamConnection *c = new StreamConnection("127.0.0.1", 30000);
    c->stopConnection();
    QVERIFY(c->getGetStream() == false);
}

//OnstreamRequest is an integration test
