#ifndef MEDIATOR_H
#define MEDIATOR_H

#include <QObject>
#include <QWidget>
#include <QThread>
#include "ui/welcomewidget.h"
#include "ui/configwidget.h"
#include "ui/overviewwidget.h"
#include "drone.h"

namespace Core {
    class Mediator;
}

/*! \brief The mediator connects all components to each other.
 */
class Mediator : public QObject
{
    Q_OBJECT

private:
    // UI elements (should already have their own thread)
    Ui::WelcomeWidget *welcomeWidget;
    Ui::ConfigWidget *configWidget;
    Ui::OverviewWidget *overviewWidget;

    // Drones
    QSet<Drone*> *drones;

    QThread persistenceThread;
public:
    explicit Mediator(QObject *parent = 0);
    ~Mediator();

    void setWelcomeWidget(Ui::WelcomeWidget *welcomeWidget);
    void setConfigWidget(Ui::ConfigWidget *configWidget);
    void setOverviewWidget(Ui::OverviewWidget *overviewWidget);

    void addDrone(Drone *drone);
    void removeDrone(Drone *drone);

};

#endif // MEDIATOR_H

