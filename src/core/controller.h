#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QThread>
#include <QList>

#include "mediator.h"
#include "communication/droneconnection.h"

#include "persistence/persistence.h"
#include "models/drone.h"
#include "detection/detectioncontroller.h"
#include "pathlogic/simplepathalgorithm.h"
#include "ui/mainwindow.h"



//namespace Core {
//class Controller;
//}

/*! \brief The Controller creates all components and puts them in their own thread if necessary.
 */
class Controller
{

public:
    Controller(MainWindow *window);
    ~Controller();
    void init();
    Mediator *getMediator() const;
    QList<Drone> *getDrones() const;
    Search *getSearch() const;

private:
    MainWindow *mainWindow;
    Mediator *mediator;
    QList<Drone> *drones;
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

