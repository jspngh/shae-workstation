#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QList>
#include <QDebug>
#include <QUuid>
#include <QUdpSocket>
#include <QThread>

#include "mediator.h"
#include "communication/droneconnection.h"
#include "communication/droneheartbeatreceiver.h"
#include "communication/dronemodule.h"
#include "detection/detectioncontroller.h"
#include "mediator.h"
#include "pathlogic/simplepathalgorithm.h"
#include "persistence/persistencecontroller.h"
#include "ui/mainwindow.h"
#include "videocontroller/videocontroller.h"
#include "models/hellomessage.h"

namespace Core {
class Controller;
}

/*! \brief The Controller creates all components and puts them in their own thread if necessary.
 */

class Controller: public QObject
{
    Q_OBJECT

public:
    Controller(MainWindow *window, QObject *p = 0);
    ~Controller();
    void init();

    // getters
    Mediator *getMediator() const;
    QList<DroneModule *> *getDrones();
    Search *getSearch() const;
    DetectionController *getDetectionController() const;
    QString getWorkstationIP() const;

    // only used for test purposes
    void setDrones(QList<DroneModule *>* list);

private:
    void processHelloMessage(QByteArray helloRaw);
    QString initWorkstationIP();
    //!< listens for hello messages from drones on the network
    void startListingForDrones();

    //!< return the dronemodule if the drone with the ip has already send a hello message
    //!< if the drone hasn't send hello yet the nullptr is returned
    DroneModule *receivedHelloFrom(QString ip);

public slots:
    void onSearchEmitted(Search* s);
    void readPendingDatagrams();
    void initStream(DroneModule* dm);
    void stopStream(DroneModule* dm);

signals:
    void startStreamSignal(Search* s, DroneModule* d, PersistenceController*p);
    void stopStreamSignal(DroneModule* d);

private:
    //TODO: due to some limitions in the streaming librairy VLC
    //      the application is only allowed to request one stream
    //      (even if there are multiple drones available).
    //      The boolean oneStream will store if a stream is already requested
    static bool oneStream = false;

    QString controllerIp = QString("10.1.1.1");
    QString workstationIP;
    MainWindow *mainWindow;
    Mediator *mediator;
    QList<DroneModule *>* drones;

    PersistenceController *persistenceController;
    PathAlgorithm *pathLogicController;
    Search *search;
    QUdpSocket *udpSocket;
    QHostAddress *host;

    QThread pathLogicThread;
    QThread droneThread;
    QThread detectorThread;
    QThread videoThread;
    QThread persistenceThread;
};

#endif // CONTROLLER_H

