#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QThread>
#include "mediator.h"
#include "communication.h"
#include "mainwindow.h"
#include "welcomewidget.h"
#include "configwidget.h"
#include "overviewwidget.h"

namespace Core {
    class Controller;
}

/*! \brief The Controller creates all components and puts them in their own thread if necessary.
 */
class Controller : public QThread
{
    Q_OBJECT

private:
    Mediator* mediator;
    Communication* communication;

    QThread mediatorThread;
    QThread communicationThread;
    QThread detectorThread;
    QThread persistenceThread;

public:
    explicit Controller(QObject *parent = 0);
    ~Controller();
    void setUiWidgets(MainWindow *window,
                      WelcomeWidget *welcomeWidget,
                      ConfigWidget *configWidget,
                      OverviewWidget *overviewWidget);

private:
    void createMediator();
    void createCommunication();
    void createDetection();
    void createPersistence();

};

#endif // CONTROLLER_H

