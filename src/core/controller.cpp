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
    drones->append(new DroneModule(6330, 5502, "127.0.0.1", "127.0.0.1", "127.0.0.1", QString("rtp://127.0.0.1:5000"),  0.0001));
    drones->append(new DroneModule(6330, 5502, "10.1.1.10", "10.1.1.1", workstationIP, QString("rtp://10.1.1.10:5000"), 0.0001));

    // create controllers
    pathLogicController = new SimplePathAlgorithm();
    persistenceController = new PersistenceController(mediator);
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
    delete search;
    // special Qt function to delete QList of pointers
    qDeleteAll(drones->begin(), drones->end());
    drones->clear();

    // delete persistenceController;
    delete pathLogicController;
    if(detectionController){
    delete detectionController;
    }
}

void Controller::init()
{
    // init the controller for single drone use.
    // configure every component with the controller
    pathLogicController->setMediator(mediator);
    for (int i = 0; i < drones->size(); i++)
        (*drones)[i]->setMediator(mediator);
    mainWindow->getConfigWidget()->setMediator(mediator);
    mainWindow->getOverviewWidget()->setMediator(mediator);

    persistenceController->moveToThread(&persistenceThread);
    pathLogicController->moveToThread(&pathLogicThread);
    DroneModule *d = drones->first();
    d->moveToThread(&droneThread);

    // start all the threads
    persistenceThread.start();
    pathLogicThread.start();
    droneThread.start();
}


void Controller::initStream(DroneModule* d)
{

    d->getStream();
    qDebug() << "Controller: stream started at drone";
    VideoSequence sequence  = d->getVideoController()->onStartStream(d->getDrone());
    detectionController = new DetectionController(search, sequence.getPath());
    qDebug() << "Controller: starting to save stream";
    // allow the stream to buffer

    QThread::sleep(1);
    //WARNING VideoCapture needs to be performed on the main thread!
    cv::VideoCapture capture = cv::VideoCapture(sequence.getPath().toStdString());
    qDebug() << "Controller: stream file has been succesfully opened";
    // allow the stream to buffer
    detectionController->setSequence(capture);

    // allow the stream to bufer for a second
    QThread::sleep(1);
    detectionController->start();

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
    d->getVideoController()->onStopStream(d->getDrone());
    d->stopStream();
    detectionController->streamFinished();
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

DetectionController *Controller::getDetectionController() const
{
    return detectionController;
}
