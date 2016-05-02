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
#include <QDialogButtonBox>

#include "core/mediator.h"
#include "models/dronestatus.h"
#include "configscriptscontroller.h"
#include "progressbarcontroller.h"
#include "gatewaydialog.h"

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

    GatewayDialog *gd;

private slots:   
    void on_configSearchButton_clicked();
    void droneDetected(DroneStatus* s);
    void pictureTimer();
    void selectedImage(int);
    void connectedToSoloNetwork();
    void notConnectedToSoloNetwork(QString);
    void startSetGateway();
    void gatewaySetted();
    void gatewayNotSetted(QString);
    void incrementProcessBar();

signals:
    void updateProgressBar(int percentage, int time);
    void connectToSoloNetwork();
    void setGateway(QString ssid, QString password);

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
    QThread csct;
    ConfigScriptsController *csc;
    QThread pbct;
    ProgressBarController *pbc;
};

#endif // WELCOMEWIDGET_H
