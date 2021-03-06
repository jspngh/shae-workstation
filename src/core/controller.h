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
#include "pathlogic/polygonpathalgorithm.h"
#include "persistence/persistencecontroller.h"
#include "ui/mainwindow.h"
#include "videocontroller/videocontroller.h"
#include "models/hellomessage.h"

namespace Core {
class Controller;
}

/*! \brief The Controller creates all components and puts them in their own thread if necessary.
 * \ingroup Core
 The Controller component is responsible for starting the different components, and launching the DroneModule.
 In order to limit the interaction required by the user, the workstation and drones on the network will dynamically connect with each other through broadcasting identification messages.
 Each of the components is started in separate threads and run asynchronously. In order to interact with support multiple drones, different DroneModules components need to launched.
 */

class Controller: public QObject
{
    Q_OBJECT

public:
    Controller(MainWindow *window, QObject *p = 0);
    ~Controller();
    void init();

    /**
     * \brief numDronesConnected returns the number of drones
     * that are connected to the the system.
     * \return positive integer (incl zero) indicating the number of drones connected.
     */
    int numDronesConnected();

    // getters
    Mediator *getMediator() const;
    QList<DroneModule *> *getDrones();
    Search *getSearch() const;
    DetectionController *getDetectionController() const;
    QString getWorkstationIP() const;
    QString getWorkstationBroadcastIp() const;
    QUdpSocket *getUdpSocketLan() const;
    QUdpSocket *getUdpSocketLo() const;


    // only used for test purposes
    void setDrones(QList<DroneModule *> *list);

// made public for testing purposes
public:
    void processHelloMessage(QByteArray helloRaw);
    //! Will retrieve the ip and broadcast address of the workstation and set in the members
    //! workstationIp and workstionBroadcastIp
    void retrieveWorkstationIpAndBroadcast();
    //! listens for hello messages from drones on the network
    void startListeningForDrones();

    //! return the dronemodule if the drone with the ip has already send a hello message
    //! if the drone hasn't send hello yet a nullptr is returned
    DroneModule *receivedHelloFrom(QString ip);

    //! will configure a drone:
    //! set the mediator, place it in a tread, append it to the dronelist, (if possible) request stream
    DroneModule *configureDrone(DroneModule *drone);


signals:
    void droneSetupFailed();

public slots:
    void onSearchEmitted(Search *s);
    void readPendingDatagrams();

private:
    //TODO: due to some limitions in the streaming librairy VLC
    //      the application is only allowed to request one stream
    //      (even if there are multiple drones available).
    //      The boolean oneStream will store if a stream is already requested.
    bool oneStream = false;

    QString workstationIp;
    QString workstationBroadcastIp;
    int helloPort = 4849;
    MainWindow *mainWindow;
    Mediator *mediator = nullptr;
    QList<DroneModule *> *drones = nullptr;

    PersistenceController *persistenceController;
    PathAlgorithm *pathLogicController;
    Search *search;
    QUdpSocket *udpSocketLan = nullptr;
    QUdpSocket *udpSocketLo = nullptr;

    QHostAddress *host;

    QThread pathLogicThread;
    QThread droneThread;
    QThread detectorThread;
    QThread videoThread;
    QThread persistenceThread;
};

#endif // CONTROLLER_H
