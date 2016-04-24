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
#include <QHBoxLayout>
#include <QTimer>

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
    void pictureTimer();
    void selectedImage(int);

private:
    Ui::WelcomeWidget *ui;
    Mediator *mediator;
    int status;
    bool droneConnected;
    int pictureTimerCounter;
    QTimer* timer;
    QStringList pictures;
    QHBoxLayout * vLayout;
    QWidget * mainScrollWidget;
};

#endif // WELCOMEWIDGET_H
