#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QThread>
#include <QList>

#include "mediator.h"
#include "communication/droneconnection.h"
#include "communication/droneheartbeatreceiver.h"

#include "persistence/persistence.h"
#include "communication/dronemodule.h"
#include "detection/detectioncontroller.h"
#include "pathlogic/simplepathalgorithm.h"
#include "ui/mainwindow.h"



//namespace Core {
//class Controller;
//}

/*! \brief The Controller creates all components and puts them in their own thread if necessary.
 */
class Controller: public QObject
{
    Q_OBJECT

public:
    Controller(MainWindow *window, QObject *p = 0);
    ~Controller();
    void init();
    Mediator *getMediator() const;
    QList<DroneModule *> *getDrones() const;
    Search *getSearch() const;

    QString getWorkstationIP() const;
    //void setWorkstationIP(const QString &value);



private:


    QString workstationIP;



    MainWindow *mainWindow;
    Mediator *mediator;
    QList<DroneModule *> *drones;
    Search *search;

    Persistence *persistenceController;
    DetectionController *detectionController;
    PathAlgorithm *pathLogicController;

    QThread pathLogicThread;
    QThread droneThread;
    QThread detectorThread;
    QThread persistenceThread;
};

#endif // CONTROLLER_H

