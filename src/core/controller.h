#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QThread>
#include <QSet>
#include "mediator.h"
#include "communication/droneconnection.h"
#include "ui/mainwindow.h"
#include "persistence/persistence.h"
#include "models/drone.h"
#include "detection/detectioncontroller.h"

namespace Core {
class Controller;
}

/*! \brief The Controller creates all components and puts them in their own thread if necessary.
 */
class Controller : public QThread
{
    Q_OBJECT

private:
    MainWindow *mainWindow;
    Mediator *mediator;
    Persistence *persistence;
    DetectionController *detectionController;
    QSet<Drone *> *drones;

    QThread mediatorThread;
    QThread droneThread;
    QThread detectorThread;
    QThread persistenceThread;

public:
    explicit Controller(MainWindow *window, QObject *parent = 0);
    ~Controller();
    /*!
     * Creates all the components.
     */
    void run() Q_DECL_OVERRIDE;

private:
    void createMediator();
    void createDrone();
    void createDetectionController();
    void createPersistence();

};

#endif // CONTROLLER_H

