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
#include "controllers/configscriptscontroller.h"
#include "controllers/progressbarcontroller.h"
#include "gatewaydialog.h"

namespace Ui {
class WelcomeWidget;
}
/*!
 * \brief The WelcomeWidget class represents the code for the welcome screen.
 * \ingroup Ui
 * The layout is defined in welcomewidget.ui
 */
class WelcomeWidget : public QWidget
{
    Q_OBJECT

public:
    //! constructor
    explicit WelcomeWidget(QWidget *parent = 0);
    //! destructor
    ~WelcomeWidget();
    //! sets the mediator
    void setMediator(Mediator *mediator);

private:
    //! \brief Sets the signal/slots.
    void setSignalSlots();
    //! called when setup is ready
    void setupReady();
    //! called when setup failed
    void setupFailed();
    //! pointer to dialog when gateway needs to be set
    GatewayDialog *gd;

private slots:
    //! slot when config is clicked, proceeds to next screen, the confg screen
    void on_configSearchButton_clicked();
    //! called when status is received
    void onDroneStatusReceived(DroneStatus* s);
    //! called when Drone setup failed
    void onDroneSetupFailure();
    //! called when the start setup button is clicked, runs the necessary scripts.
    void on_startSetupButton_clicked();
    //! \brief Reset picture timer.
    void pictureTimer();
    //! \brief Change the selected image in the ui.
    void selectedImage(int);
    //! slot called when connected to the right network
    void connectedToSoloNetwork();
    //! slot called when not connected to the solo network
    void notConnectedToSoloNetwork(QString);
    //! slot called to setup the gateway
    void startSetGateway();
    //! slot called when gateway is set
    void gatewaySet();
    //! slot called when gateway is not set
    void gatewayNotSet(QString);
    //! slot to increment the progressbar
    void incrementProcessBar();
signals:
    //! signal the incremtent the progressbar
    void updateProgressBar(int percentage, int time);
    //! signal to connect to the solo network
    void connectToSoloNetwork();
    //! signal to set the gateway
    void setGateway(QString ssid, QString password);

private:
    //! pointer to layout
    Ui::WelcomeWidget *ui;
    //! pointer to mediator
    Mediator *mediator;
    //! status is an integer
    int status;
    //! bool that says if a drone is connected or not
    bool droneConnected;
    //! counter to switch to next screenshot in the welcome screen
    int pictureTimerCounter;
    //! A timer to keep time for the current screenshot
    QTimer* timer;
    //! list of names of screenshots
    QStringList pictures;
    //! layout for the screenshots
    QHBoxLayout * vLayout;
    //! scrollwidget
    QWidget * mainScrollWidget;
    //! configuration scripts controller thread
    QThread csct;
    //! ConfigurationScripts Controller runs the configuration scripts
    ConfigScriptsController *csc;
    //! thread for the progressbarcontroller
    QThread pbct;
    //! progressbarController controls the progressbar
    ProgressBarController *pbc;
};

#endif // WELCOMEWIDGET_H
