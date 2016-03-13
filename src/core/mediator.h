#ifndef MEDIATOR_H
#define MEDIATOR_H

#include <QObject>
#include <QThread>
#include "communication.h"
#include "ui/mainwindow.h"

namespace Core {
    class Mediator;
}

/*! \brief The mediator connects all components to each other.
 */
class Mediator : public QObject
{
    Q_OBJECT

private:
    MainWindow *mainWindow;
    Communication *communication;

public:
    explicit Mediator(MainWindow *window, QObject *parent = 0);
    ~Mediator();

};

#endif // MEDIATOR_H

