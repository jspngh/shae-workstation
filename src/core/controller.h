#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QThread>
#include <QSet>
#include "mediator.h"
#include "communication.h"
#include "mainwindow.h"
#include "drone.h"

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
    Communication *communication;
    QSet<Drone*> *drones;

    QThread mediatorThread;
    QThread communicationThread;
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
    void createCommunication();
    void createDrone();
    void createDetection();
    void createPersistence();

};

#endif // CONTROLLER_H

