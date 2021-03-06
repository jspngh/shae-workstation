#include <unistd.h>

#include <QtNetwork>
#include <QtDebug>

#include "streamconnection.h"

StreamConnection::StreamConnection(const QString hostName, quint16 port, QObject *parent)
    : QObject(parent),
      droneIpAddress(hostName),
      streamPort(port),
      getStream(true)
{
}

StreamConnection::~StreamConnection()
{
}

void StreamConnection::onStreamRequest()
{
    qDebug() << "StreamConnection::onStreamRequest";
    QString serverName = droneIpAddress;
    quint16 serverPort = streamPort;

    const int Timeout = 20 * 1000;

    QTcpSocket socket;
    socket.connectToHost(serverName, serverPort);

    if (!socket.waitForConnected(Timeout)) {
        emit streamError(socket.error(), socket.errorString());
        qDebug() << "StreamConnection failed at " << droneIpAddress << ":" << streamPort;
        return;
    }
    qDebug() << "connected with the streamsocket";

    while (getStream) {
        usleep(1000);
    }
}

bool StreamConnection::getGetStream() const
{
    return getStream;
}

quint16 StreamConnection::getStreamPort() const
{
    return streamPort;
}

QString StreamConnection::getDroneIpAddress() const
{
    return droneIpAddress;
}

void StreamConnection::stopConnection()
{
    getStream = false;
}
