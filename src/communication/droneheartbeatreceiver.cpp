#include "droneheartbeatreceiver.h"



DroneHeartBeatReceiver::DroneHeartBeatReceiver(const QString ip, quint16 port, QObject *parent)
    : QObject(parent), workstationIpAdress(ip), port(port)
{
    server = new QTcpServer();
    server->listen(QHostAddress(ip), port);

    //connect receive slot to newConnection signal of Qt so this will get called on each connection
    connect(server, &QTcpServer::newConnection, this, &DroneHeartBeatReceiver::receiveHeartbeat);
}

DroneHeartBeatReceiver::~DroneHeartBeatReceiver()
{
    delete server;
}

void DroneHeartBeatReceiver::receiveHeartbeat()
{
    const int Timeout = 5 * 1000;

    //get socket that is connected
    QTcpSocket* clientConnection = server->nextPendingConnection();
    //make sure socket gets deleted if disconnected
    connect(clientConnection, &QAbstractSocket::disconnected, clientConnection, &QObject::deleteLater);
    //copied from droneconnection.cpp
    while (clientConnection->bytesAvailable() < (int)sizeof(quint16)) {
        if (!clientConnection->waitForReadyRead(Timeout)) {
            emit droneHeartBeatError(clientConnection->error(), clientConnection->errorString());
            return;
        }
    }

    quint16 blockSize;
    QDataStream in(clientConnection);
    in.setVersion(QDataStream::Qt_4_0);
    in >> blockSize;

    while (clientConnection->bytesAvailable() < blockSize) {
        if (!clientConnection->waitForReadyRead(Timeout)) {
            emit droneHeartBeatError(clientConnection->error(), clientConnection->errorString());
            return;
        }
    }

    QByteArray raw;
    in >> raw;
    QString response = QTextCodec::codecForMib(1016)->toUnicode(raw);

    emit droneHeartBeat(response);

    clientConnection->disconnectFromHost();

}

