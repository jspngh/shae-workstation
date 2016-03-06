#include <QtNetwork>

#include "droneconnection.h"

DroneConnection::DroneConnection(QObject *parent)
    : QThread(parent), quit(false)
{
}

DroneConnection::~DroneConnection()
{
    mutex.lock();
    quit = true;
    cond.wakeOne();
    mutex.unlock();
    wait();
}

void DroneConnection::droneRequest(const QString &hostName, quint16 port, const QString &message)
{

    QMutexLocker locker(&mutex);
    this->jsonMessage = message;
    this->droneIpAddress = hostName;
    this->port = port;

    if (!isRunning())
        start();
    else
        cond.wakeOne();
}

void DroneConnection::run()
{
    mutex.lock();

    QString message = jsonMessage;
    QString serverName = droneIpAddress;
    quint16 serverPort = port;
    mutex.unlock();

    while (!quit) {

        const int Timeout = 5 * 1000;

        QTcpSocket socket;
        socket.connectToHost(serverName, serverPort);

        if (!socket.waitForConnected(Timeout)) {
            emit error(socket.error(), socket.errorString());
            return;
        }

        QByteArray block;
        QDataStream out(&block, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_4_0);

        // First send the lenght of the message, then the actual message
        out << (quint16)0;
        out << message;
        socket.write(block);
        out.device()->seek(0);
        out << (quint16)(block.size() - sizeof(quint16));

        while (socket.bytesAvailable() < (int)sizeof(quint16)) {
            if (!socket.waitForReadyRead(Timeout)) {
                emit error(socket.error(), socket.errorString());
                return;
            }
        }

        quint16 blockSize;
        QDataStream in(&socket);
        in.setVersion(QDataStream::Qt_4_0);
        in >> blockSize;

        while (socket.bytesAvailable() < blockSize) {
            if (!socket.waitForReadyRead(Timeout)) {
                emit error(socket.error(), socket.errorString());
                return;
            }
        }

        mutex.lock();
        QString response;
        in >> response;
        emit droneResponse(response);

        cond.wait(&mutex);
        message = jsonMessage;
        serverName = droneIpAddress;
        serverPort = port;
        mutex.unlock();
    }
}
