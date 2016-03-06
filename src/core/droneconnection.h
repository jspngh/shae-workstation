#ifndef DRONECONNECTION_H
#define DRONECONNECTION_H

#include <QThread>
#include <QMutex>
#include <QWaitCondition>

class DroneConnection: public QThread
{
    Q_OBJECT

public:
    DroneConnection(QObject *parent = 0);
    ~DroneConnection();

    void droneRequest(const QString &hostName, quint16 port, const QString &message);
    void run() Q_DECL_OVERRIDE;

signals:
    void droneResponse(const QString &fortune);
    void error(int socketError, const QString &message);

private:
    QString jsonMessage; /*!< The message to send, in Json format */
    QString droneIpAddress; /*!< The IP address of the drone, this will be 10.1.1.10 */
    quint16 port; /*!< The port number that will be used to connect to the drone */
    QMutex mutex;
    QWaitCondition cond;
    bool quit;
};

#endif // DRONECONNECTION_H
