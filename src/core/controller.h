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
    void initStream(DroneModule* d);
    void stopStream(DroneModule* d);

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

    // return the dronemodule if the drone with the ip has already send a hello message
    // if the drone hasn't send hello yet the nullptr is returned
    DroneModule *receivedHelloFrom(QString ip);

public slots:
    void onSearchEmitted(Search* s);
    void readPendingDatagrams();

private:
    QString controllerIp = QString("10.1.1.1");
    QString workstationIP;
    MainWindow *mainWindow;
    Mediator *mediator;
    QList<DroneModule *>* drones;

    PersistenceController *persistenceController;
    VideoController *videoController;
    DetectionController *detectionController = nullptr;
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

