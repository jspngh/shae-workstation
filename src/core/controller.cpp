#include "controller.h"
#include <QUuid>


Controller::Controller(MainWindow *window, QObject *p)
    : QObject(p)
{
    mainWindow = window;

    // create the mediator. Note: the same mediator object must be shared among all the components!
    mediator = new Mediator();

    workstationIP = initWorkstationIP();

    drones = new QList<DroneModule*>();
    // dronePort, streamPort, droneIp, controllerIp, workstationIp
    drones->append(new DroneModule(6330, 5502, "127.0.0.1", "127.0.0.1", "127.0.0.1", QString("rtp://127.0.0.1:5000"),  0.0001, true));
    drones->append(new DroneModule(6330, 5502, "10.1.1.10", "10.1.1.1", workstationIP, QString("sololink.sdp"), 0.0001));

    // create controllers
    pathLogicController = new SimplePathAlgorithm();
    persistenceController = new PersistenceController();

    // add signal/slot
    mediator->addSlot(this, SLOT(onSearchEmitted(Search *)), QString("startSearch(Search*)"));
    mediator->addSignal(this, (char *) SIGNAL(startStreamSignal(Search*, DroneModule*, PersistenceController*)), QString("startStreamSignal(Search*,DroneModule*,PersistenceController*)"));
    mediator->addSignal(this, (char *) SIGNAL(stopStreamSignal(DroneModule*)), QString("stopStreamSignal(DroneModule*)"));
    mediator->addSlot(this, (char *) SLOT(initStream(DroneModule*)), QString("startStreamWorkstation(DroneModule*)"));
}

Controller::~Controller()
{
    // stop all the threads in order to safely delete them afterwards
    droneThread.quit();
    droneThread.wait();
    pathLogicThread.quit();
    pathLogicThread.wait();
    persistenceThread.quit();
    persistenceThread.wait();

    // delete the mediator and the search object
    delete mediator;
    // special Qt function to delete QList of pointers
    qDeleteAll(drones->begin(), drones->end());
    drones->clear();

    // delete persistenceController;
    delete pathLogicController;
}

void Controller::init()
{
    // configure every component with the mediator
    pathLogicController->setMediator(mediator);
    for (int i = 0; i < drones->size(); i++)
        (*drones)[i]->setMediator(mediator);
    mainWindow->getConfigWidget()->setMediator(mediator);
    mainWindow->getOverviewWidget()->setMediator(mediator);
    persistenceController->setMediator(mediator);

    // place every component in a different thread
    persistenceController->moveToThread(&persistenceThread);
    pathLogicController->moveToThread(&pathLogicThread);
    for (int i = 0; i < drones->size(); i++)
        (*drones)[i]->moveToThread(&droneThread);

    // already start the stream on the drone
    drones->first()->getStreamConnection();

    // start all the threads
    persistenceThread.start();
    pathLogicThread.start();
    droneThread.start();

}

 void Controller::initStream(DroneModule* dm)
{
     emit startStreamSignal(search, dm, persistenceController);
}

QString Controller::initWorkstationIP()
{
    foreach(const QHostAddress & address, QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol
                && address != QHostAddress(QHostAddress::LocalHost))
            return address.toString();
    }
    return QString();
}

void Controller::stopStream(DroneModule* d)
{
    emit stopStreamSignal(d);
}

void Controller::onSearchEmitted(Search* s){
    qDebug() << "Controller::saved search";
    search = s;
}

/*****************
 *    Getters
 *****************/

Mediator *Controller::getMediator() const
{
    return mediator;
}

QList<DroneModule *> *Controller::getDrones()
{
    return drones;
}


void Controller::setDrones(QList<DroneModule *>* list)
{
    drones = list;
}

Search *Controller::getSearch() const
{
    return search;
}

QString Controller::getWorkstationIP() const
{
    return workstationIP;
}
