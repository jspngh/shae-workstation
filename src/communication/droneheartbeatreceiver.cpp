#include "droneheartbeatreceiver.h"



DroneHeartBeatReceiver::DroneHeartBeatReceiver(const QString ip, QObject *parent)
    : QObject(parent)
{
    server = new QTcpServer();
    server->listen(QHostAddress(ip));
    workstationHeartbeatPort = server->serverPort();

    //connect receive slot to newConnection signal of Qt so this will get called on each connection
    connect(server, &QTcpServer::newConnection, this, &DroneHeartBeatReceiver::receiveHeartbeat);
}

DroneHeartBeatReceiver::~DroneHeartBeatReceiver()
{
    delete server;
}

//this method only gets called by a signal if a client is trying to connect.
void DroneHeartBeatReceiver::receiveHeartbeat()
{
    const int Timeout = 20 * 1000;
    qDebug() << "receiveHeartbeat";

    //get socket that is connected
    QTcpSocket *clientConnection = server->nextPendingConnection();
    //make sure socket gets deleted if disconnected
    connect(clientConnection, &QAbstractSocket::disconnected, clientConnection, &QObject::deleteLater);

    //rest is copied and refactored from droneconnection.cpp
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
    qDebug() << raw;
    QString response = QTextCodec::codecForMib(1016)->toUnicode(raw);

    emit droneHeartBeat(response);

    clientConnection->disconnectFromHost();

}

quint16 DroneHeartBeatReceiver::getWorkstationHeartbeatPort() const
{
    return workstationHeartbeatPort;
}

void DroneHeartBeatReceiver::setWorkstationHeartbeatPort(const quint16 &value)
{
    workstationHeartbeatPort = value;
}


