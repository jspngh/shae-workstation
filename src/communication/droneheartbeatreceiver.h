#ifndef DRONEHEARTBEATRECEIVER_H
#define DRONEHEARTBEATRECEIVER_H

#include <QObject>
#include <QTcpServer>
#include <QAbstractSocket>
#include <QtNetwork>
#include <QHostAddress>

/*!
 * \brief The DroneHeartBeatReceiver class
 * \ingroup Communication
 */


class DroneHeartBeatReceiver: public QObject
{
    Q_OBJECT

public:
    DroneHeartBeatReceiver();
    DroneHeartBeatReceiver(const QString ip, QObject *p = 0);
    ~DroneHeartBeatReceiver();


    quint16 getWorkstationHeartbeatPort() const;
    void setWorkstationHeartbeatPort(const quint16 &value);

public slots:
    /*! \brief This function gets called everytime something tries to connect to the QTcpServer.
    This method reads the incoming heartbeat and emits a signal (droneHeartBeat) */
    void receiveHeartbeat();

signals:
    /*! emit droneHeartbeat after receiving a heartbeat message. This signal is comparable to DroneConnection::droneResponse.
    This signal should also be connected to onDroneRespone of the drone class, which will eventually call droneStatusReceived(DroneStatus).
    The connection is made in the drone constructor*/
    void droneHeartBeat(const QString heartbeat);
    //! this error signal gets emitted if something goes wrong with the socket of the heratbeatreceiver.
    void droneHeartBeatError(int socketError, const QString &message);

private:

    quint16 workstationHeartbeatPort;
    QTcpServer *server;
};

#endif // DRONEHEARTBEATRECEIVER_H
