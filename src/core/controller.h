#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QList>
#include <QDebug>

#include "mediator.h"
#include <QThread>
#include "communication/droneconnection.h"
#include "communication/droneheartbeatreceiver.h"
#include "communication/dronemodule.h"
#include "detection/detectioncontroller.h"
#include "mediator.h"
#include "pathlogic/simplepathalgorithm.h"
#include "persistence/persistencecontroller.h"
#include "ui/mainwindow.h"
#include "videocontroller/videocontroller.h"

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

    Mediator *getMediator() const;
    QList<DroneModule *> *getDrones();
    void setDrones(QList<DroneModule *>* list);

    Search *getSearch() const;
    DetectionController *getDetectionController() const;
    QString initWorkstationIP();

    QString getWorkstationIP() const;
public slots:
    void onSearchEmitted(Search* s);
private:
    QString workstationIP;
    MainWindow *mainWindow;
    Mediator *mediator;
    QList<DroneModule *>* drones;

    PersistenceController *persistenceController;
    VideoController *videoController;
    DetectionController *detectionController = nullptr;
    PathAlgorithm *pathLogicController;
    Search* search;

    QThread pathLogicThread;
    QThread droneThread;
    QThread detectorThread;
    QThread videoThread;
    QThread persistenceThread;
};

#endif // CONTROLLER_H

