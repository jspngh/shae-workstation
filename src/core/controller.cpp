
#include "controller.h"
#include <QUuid>

Controller::Controller(MainWindow *window, QObject *p)
    : QObject(p)
{
    mainWindow = window;

    // create the mediator. Note: the same mediator object must be shared among all the components!
    mediator = new Mediator();

    //set workstationIP
    foreach (const QHostAddress &address, QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != QHostAddress(QHostAddress::LocalHost))
            workstationIP = address.toString();
    }
    //TODO: delete override
    workstationIP = "127.0.0.1";

    // create drones
    // TODO: drone info (IP, port, etc) should be set elsewhere
    drones.append(new DroneModule(6330, 5502, workstationIP, QString("rtp://127.0.0.1:5000"),  0.0001));
    drones.append(new DroneModule(6330, 5502, "10.1.1.10", QString("rtp://10.1.1.10:5000"), 0.0001));

    // create controllers
    //detectionController = new DetectionController(mediator);
    //persistenceController = new Persistence(mediator);
    pathLogicController = new SimplePathAlgorithm();
}

Controller::~Controller()
{
    // stop all the threads in order to safely delete them afterwards
    droneThread.quit();
    droneThread.wait();
    pathLogicThread.quit();
    pathLogicThread.wait();
    // persistenceThread.quit();
    // persistenceThread.wait();

    delete mediator;

    // special Qt function to delete QList of pointers
    qDeleteAll(drones.begin(), drones.end());
    drones.clear();

    // delete detectionController;
    // delete persistenceController;
    delete pathLogicController;
}

void Controller::init()
{
    // configure every component with the controller
    mainWindow->getConfigWidget()->setMediator(mediator);
    mainWindow->getOverviewWidget()->setMediator(mediator);
    pathLogicController->setMediator(mediator);
    for (int i = 0; i < drones.size(); i++) {
        drones[i]->setController(this);
        /* drones[i]->getStream(); */
    }

    // set every component in a different thread
    // NOTE: all the drones are placed in the same thread (TODO: make thread for every drone)

    // detectionController->moveToThread(&detectorThread);
    // persistenceController->moveToThread(&persistenceThread);
    pathLogicController->moveToThread(&pathLogicThread);
    for (int i = 0; i < drones.size(); i++)
        drones[i]->moveToThread(&droneThread);

    // start all the threads
    // detectorThread.start();
    // persistenceThread.start();
    droneThread.start();
    pathLogicThread.start();
}

/*****************
 *    Getters
 *****************/

Mediator *Controller::getMediator() const
{
    return mediator;
}

QList<DroneModule *> Controller::getDrones() const
{
    return drones;
}

QString Controller::getWorkstationIP() const
{
    return workstationIP;
}

