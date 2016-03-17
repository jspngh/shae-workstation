#include <QDebug>

#include "communication.h"

/*! \brief This class is deprecated and no longer used
 *
 *
*/

Communication::~Communication()
{

}

Communication::Communication(QString serverIp, int portNr)
    : serverIp(serverIp), portNr(portNr)
{
    connect(&drone, SIGNAL(droneResponse(QString)),
            this, SLOT(processResponse(QString)));
    connect(&drone, SIGNAL(error(int,QString)),
            this, SLOT(processError(int,QString)));
}

int Communication::doRequest(const QString &message)
{
    drone.droneRequest(serverIp, (quint16) portNr, message);
    //qDebug() << "After drone Request";
    return 0;
}

void Communication::processResponse(const QString &response)
{
    //qDebug() << "In processResponse";
    qDebug() << response;
}

void Communication::processError(int socketError, const QString &message)
{
    qDebug() << message;
}
