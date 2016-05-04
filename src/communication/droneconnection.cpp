#include <QtNetwork>
#include <QtDebug>
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

void DroneConnection::onDroneRequest(QString m)
{
    QString message = m;
    QString serverName = droneIpAddress;
    quint16 serverPort = port;

    const int Timeout = 20 * 1000;

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

    quint16 statusCode;
    QDataStream in(&socket);
    in.setVersion(QDataStream::Qt_4_0);
    in >> statusCode;

    if (statusCode == 300) {
        quint16 blockSize;

        while (socket.bytesAvailable() < (int)sizeof(quint16)) {
            if (!socket.waitForReadyRead(Timeout)) {
                emit droneResponseError(socket.error(), socket.errorString());
                return;
            }
        }

        in >> blockSize;

        while (socket.bytesAvailable() < blockSize) {
            if (!socket.waitForReadyRead(Timeout)) {
                emit droneResponseError(socket.error(), socket.errorString());
                return;
            }
        }

        QByteArray raw;
        in >> raw;
        // qDebug() << raw;
        QString response = QTextCodec::codecForMib(1016)->toUnicode(raw);

        emit droneResponse(response);
    }
}
