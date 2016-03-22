#include <QtNetwork>

#include "droneconnection.h"

DroneConnection::DroneConnection(const QString hostName, quint16 port, QObject *parent)
    : QObject(parent),
      droneIpAddress(hostName),
      port(port)
{

}

DroneConnection::~DroneConnection()
{

}

void DroneConnection::onDroneRequest(const QString &m)
{
    QString message = m;
    QString serverName = droneIpAddress;
    quint16 serverPort = port;

    const int Timeout = 5 * 1000;

    QTcpSocket socket;
    socket.connectToHost(serverName, serverPort);

    if (!socket.waitForConnected(Timeout)) {
        emit droneResponseError(socket.error(), socket.errorString());
        return;
    }

    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);

    out << message.toUtf8();
    socket.write(block);

    while (socket.bytesAvailable() < (int)sizeof(quint16)) {
        if (!socket.waitForReadyRead(Timeout)) {
            emit droneResponseError(socket.error(), socket.errorString());
            return;
        }
    }

    quint16 blockSize;
    QDataStream in(&socket);
    in.setVersion(QDataStream::Qt_4_0);
    in >> blockSize;

    while (socket.bytesAvailable() < blockSize) {
        if (!socket.waitForReadyRead(Timeout)) {
            emit droneResponseError(socket.error(), socket.errorString());
            return;
        }
    }

    // mutex.lock();
    QByteArray raw;
    in >> raw;
    QString response = QTextCodec::codecForMib(1016)->toUnicode(raw);

    emit droneResponse(response);

}
