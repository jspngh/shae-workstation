#include "controller_test.h"
#include <QRegExp>


Controller_Test::Controller_Test()
{

}

void Controller_Test::initTestCase()
{

}

void Controller_Test::cleanupTestCase()
{

}

void Controller_Test::testConstructor()
{
    Controller *ctrl = new Controller(nullptr);

    QVERIFY(ctrl->getMediator() != nullptr);
    QVERIFY(ctrl->getDrones() != nullptr);
}

void Controller_Test::testInitWorkstationIp()
{
    Controller *ctrl = new Controller(nullptr);

    QRegExp rx("^((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.){3}(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$");
    QVERIFY(rx.exactMatch(ctrl->getWorkstationIP()));
}

void Controller_Test::testInitBroadcastIp()
{
    Controller *ctrl = new Controller(nullptr);

    QRegExp rx("^((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.){3}(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$");
    QVERIFY(rx.exactMatch(ctrl->getWorkstationBroadcastIp()));
}

void Controller_Test::testUdpSockets()
{
    Controller *ctrl = new Controller(nullptr);
    ctrl->startListeningForDrones();
    QVERIFY(ctrl->getUdpSocketLo() != nullptr);
    QVERIFY(ctrl->getUdpSocketLan() != nullptr);
}
