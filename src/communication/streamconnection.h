#ifndef STREAMCONNECTION_H
#define STREAMCONNECTION_H

#include <QObject>
#include <QMutex>
#include <QDebug>

#include <QWaitCondition>
#include "core/mediator.h"


/*! \brief The StreamConnection class has as its goal to connect to port 5502 of the Solo.
 * This is necessary to be able to capture the stream, which is only started after this connection has been made.
 * By connecting on port 5502, we essentially emulate the Android application, which requires the stream to display.
*/
class StreamConnection: public QObject
{
    Q_OBJECT

public:
    StreamConnection(const QString hostName, quint16 port, QObject *p = 0);
    ~StreamConnection();

    void stopConnection();

public slots:
    void onStreamRequest();

signals:
    void streamError(int socketError, const QString &message);

private:
    QString droneIpAddress; /*!< The IP address of the drone, this will be 10.1.1.10 */
    quint16 streamPort; /*!< The port number we need to setup a connection with, this will be 5502 */
    bool getStream; /*!< A boolean that indicates if we still need the connection */
};

#endif // STREAMCONNECTION_H
