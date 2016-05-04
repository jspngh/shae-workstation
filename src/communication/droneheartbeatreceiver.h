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
 This class is responsible for receiving the continous heartbeats sent by the drone. It passes on the heartbeat to the DroneModule.

 */


class DroneHeartBeatReceiver: public QObject
{
    Q_OBJECT

public:
    //! default constructor, not to be used.
    DroneHeartBeatReceiver();

    /*!
     * \brief DroneHeartBeatReceiver constructor, starts listening to incoming connection on a free port
     * \param ip is the Ipadress that is used to listen on for incoming connections.
     * \param p is the parent QObject, not used
     */
    DroneHeartBeatReceiver(const QString ip, QObject *p = 0);

    //! default destructor, closes and deletes the server
    ~DroneHeartBeatReceiver();

    //! simple getter
    quint16 getWorkstationHeartbeatPort() const;

    //! simple setter
    void setWorkstationHeartbeatPort(const quint16 &value);

public slots:
    /*! \brief This function gets called everytime something tries to connect to the QTcpServer.
    This method reads the incoming heartbeat and emits a signal (droneHeartBeat) */
    void receiveHeartbeat();

signals:

    /*!  \brief emit droneHeartbeat after receiving a heartbeat message.
     *  This signal is comparable to DroneConnection::droneResponse.
     This signal should also be connected to onDroneRespone of the drone class, which will eventually call droneStatusReceived(DroneStatus).
     The connection is made in the drone constructor
    */
    void droneHeartBeat(const QString heartbeat);

    //! this error signal gets emitted if something goes wrong with the socket of the heratbeatreceiver.
    void droneHeartBeatError(int socketError, const QString &message);

private:

    //! the port that is used to listen for heartbeats is generated in the constructor
    quint16 workstationHeartbeatPort;

    //! the QTcpServer that is udes to listen to incoming Tcp connections
    QTcpServer *server;
};

#endif // DRONEHEARTBEATRECEIVER_H
