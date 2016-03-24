#ifndef DRONEHEARTBEATRECEIVER_H
#define DRONEHEARTBEATRECEIVER_H

#include <QObject>
#include <QTcpServer>
#include <QAbstractSocket>
#include <QtNetwork>
#include "core/controller.h"
#include <QHostAddress>


class Controller;

class DroneHeartBeatReceiver: public QObject
{
    Q_OBJECT

public:
    DroneHeartBeatReceiver();
    DroneHeartBeatReceiver(const QString ip, quint16 port, QObject*p =0);
    ~DroneHeartBeatReceiver();

    Controller *getController() const;
    void setController(Controller *value);

    quint16 getWorkstationHeartbeatPort() const;
    void setWorkstationHeartbeatPort(const quint16 &value);

public slots:
    void receiveHeartbeat();

signals:
    /*! emit droneHeartbeat after receiving a heartbeat message. This signal is comparable to DroneConnection::droneResponse.
    This signal should also be connected to onDroneRespone of the drone class, which will eventually call droneStatusReceived(DroneStatus).
    The connection is made in the drone constructor*/
    void droneHeartBeat(const QString heartbeat);
    void droneHeartBeatError(int socketError, const QString &message);

private:
    Controller* controller;
    quint16 workstationHeartbeatPort;
    QTcpServer* server;

};

#endif // DRONEHEARTBEATRECEIVER_H
