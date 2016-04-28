#ifndef DRONECONNECTION_H
#define DRONECONNECTION_H

#include <QObject>
#include <QMutex>
#include <QWaitCondition>
#include "core/mediator.h"

/*!
 * \brief The DroneConnection class
 * \ingroup Communication
 * This class allows sending messages over TCP to the drone, and getting an answer from the drone.
 */

class DroneConnection: public QObject
{
    Q_OBJECT

public:
    DroneConnection(const QString hostName, quint16 port, QObject *p = 0);
    ~DroneConnection();

public slots:
    void onDroneRequest(QString message);

signals:
    void droneResponse(const QString &fortune);
    void droneResponseError(int socketError, const QString &message);

private:
    QString droneIpAddress; /*!< The IP address of the drone, this will be 10.1.1.10 */
    quint16 port; /*!< The port number that will be used to connect to the drone */

};

#endif // DRONECONNECTION_H
