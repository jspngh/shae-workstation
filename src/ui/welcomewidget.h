#ifndef WELCOMEWIDGET_H
#define WELCOMEWIDGET_H

#include <QWidget>
#include <QStackedWidget>
#include <QProgressDialog>
#include <QFileDialog>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QDateTime>

#include "core/mediator.h"
#include "models/dronestatus.h"

namespace Ui {
class WelcomeWidget;
}

class WelcomeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit WelcomeWidget(QWidget *parent = 0);
    ~WelcomeWidget();

    void setMediator(Mediator *mediator);

private:
    void setSignalSlots();

    void setupReady();

private slots:   
    void on_configSearchButton_clicked();
    void droneDetected(DroneStatus* s);

private:
    Ui::WelcomeWidget *ui;
    Mediator *mediator;
};

#endif // WELCOMEWIDGET_H
