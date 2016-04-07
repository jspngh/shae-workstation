#include "controller.h"
#include <QUuid>

Controller::Controller(MainWindow *window, QObject *p)
    : QObject(p)
{
    mainWindow = window;

    // create the mediator. Note: the same mediator object must be shared among all the components!
    mediator = new Mediator();

    workstationIP = initWorkstationIP();
    // qDebug() << workstationIP;

    // create drones
    // TODO: drone info (IP, port, etc) should be set elsewhere
    drones.append(new DroneModule(6330, 5502, "127.0.0.1", QString("rtp://127.0.0.1:5000"),  0.0001));
    drones.append(new DroneModule(6330, 5502, "10.1.1.10", QString("rtp://10.1.1.10:5000"), 0.0001));

    // create controllers
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
    pathLogicController->setMediator(mediator);
    for (int i = 0; i < drones.size(); i++)
        drones[i]->setController(this);
    mainWindow->getConfigWidget()->setMediator(mediator);
    mainWindow->getOverviewWidget()->setMediator(mediator);

    // set every component in a different thread
    // note: all the drones are placed in the same thread (TODO: make thread for every drone)
    // persistenceController->moveToThread(&persistenceThread);
    pathLogicController->moveToThread(&pathLogicThread);
    for (int i = 0; i < drones.size(); i++)
        drones[i]->moveToThread(&droneThread);

    // start all the threads
    pathLogicThread.start();
    droneThread.start();
    // persistenceThread.start();
}

QString Controller::initWorkstationIP()
{
    foreach(const QHostAddress & address, QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol
                && address != QHostAddress(QHostAddress::LocalHost))
            return address.toString();
    }
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

