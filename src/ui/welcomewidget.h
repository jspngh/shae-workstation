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
#include "progressbarcontroller.h"

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
    QString connect_to_solo_wifi();

private slots:   
    void on_configSearchButton_clicked();
    void droneDetected(DroneStatus* s);
    void pictureTimer();
    void selectedImage(int);

signals:
    void updateProgressBar(int percentage, int time);

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
