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

        out << message;
        socket.write(block);

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
        //qDebug() << blockSize;

        while (socket.bytesAvailable() < blockSize) {
            if (!socket.waitForReadyRead(Timeout)) {
                emit error(socket.error(), socket.errorString());
                return;
            }
        }

        mutex.lock();
        QByteArray raw;
        in >> raw;
        QString response = QString::fromStdString(raw.toStdString());
        emit droneResponse(response);

        cond.wait(&mutex);
        message = jsonMessage;
        serverName = droneIpAddress;
        serverPort = port;
        mutex.unlock();
    }
}
