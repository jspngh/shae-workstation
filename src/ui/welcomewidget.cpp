#include "welcomewidget.h"
#include "ui_welcomewidget.h"
#include "clickablelabel.h"
#include <QDebug>
#include <QDir>
#include <QPixmap>
#include <QTimer>
#include <QProcess>
#include <QStandardPaths>
#include <QFuture>
#include <QtConcurrent/QtConcurrent>


WelcomeWidget::WelcomeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WelcomeWidget)
{
    ui->setupUi(this);

    //Bottem layout setup

    ui->progressBar->setValue(0);
    ui->configSearchButton->setText("Start Setup");

    //non ui fields setup

    status = 0;
    droneConnected = false;
    pictureTimerCounter = 0;
    pictures = QDir( ":/ui/screens" ).entryList();

    //scroll area setup

    ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    mainScrollWidget = new QWidget(ui->hintView);
    vLayout = new QHBoxLayout(mainScrollWidget);

    for(int i = 0; i < pictures.size(); i++)
    {
        ClickableLabel *pictureLabel = new ClickableLabel("", i, this);
        QPixmap pic = QPixmap(QString(":/ui/screens/").append(pictures.at(i)));
        pictureLabel->setPixmap(pic.scaled(100,70,Qt::KeepAspectRatio));
        pictureLabel->setAlignment(Qt::AlignCenter);
        pictureLabel->setMargin(8);
        connect(pictureLabel, SIGNAL(clicked(int)), this, SLOT(selectedImage(int)));
        vLayout->addWidget(pictureLabel);
    }

    ui->scrollArea->setWidget(mainScrollWidget);

    //main picture setup
    ui->hintView->setAlignment(Qt::AlignCenter);

    //time setup

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(pictureTimer()));
    timer->start(1);

    // Create and init configScriptCOntroller
    csc = new ConfigScriptsController();
    csc->moveToThread(&csct);
    connect(this, SIGNAL(connect_to_solo_network()), csc, SLOT(connect_to_solo_network()));
    connect(csc, SIGNAL(connected_to_solo_network()), this, SLOT(connected_to_solo_network()));
    connect(csc, SIGNAL(not_connected_to_solo_network(QString)), this, SLOT(not_connected_to_solo_network(QString)));
    connect(this, SIGNAL(set_gateway(QString, QString)), csc, SLOT(set_gateway(QString, QString)));
    connect(csc, SIGNAL(gateway_setted()), this, SLOT(gateway_setted()));
    connect(csc, SIGNAL(gateway_not_setted(QString)), this, SLOT(gateway_not_setted(QString)));
    csct.start();

    // Create and init progressBarController
    pbc = new ProgressBarController();
    pbc->setProgressBar(ui->progressBar);
    pbc->moveToThread(&pbct);
    connect(this, SIGNAL(updateProgressBar(int, int)), pbc, SLOT(update(int, int)));
    connect(pbc, SIGNAL(incrementProcessBarr()), this, SLOT(incrementProcessBar()));
    pbct.start();
}

WelcomeWidget::~WelcomeWidget()
{
    for(QObject* w : vLayout->children())
    {
        delete w;
    }
    delete vLayout;
    delete mainScrollWidget;
    delete ui;
    delete timer;
}

void WelcomeWidget::setMediator(Mediator *mediator)
{
    this->mediator = mediator;
    setSignalSlots();
}

void WelcomeWidget::setSignalSlots()
{
    mediator->addSlot(this, SLOT(droneDetected(DroneStatus*)), QString("droneStatusReceived(DroneStatus*)"));
}

void WelcomeWidget::setupReady()
{
     if(status > 0)
         ui->configSearchButton->setEnabled(true);
     else
         droneConnected = true;

}

/***
 * Connecting on controller's Wifi (make sure controller is turned on).
 * \nSetting up gateway on the controller.
 * \nReconnecting to controller's network.
 * \nSearching for drones on the network.
 * \nSearching for GPS signal (may take a while).
 *
 *
 * */

/*************
 *  SLOTS
 * **********/

void WelcomeWidget::on_configSearchButton_clicked()
{
    if(status == 0)
    {
        // Set statusLabel
        ui->statusLabel->setText("Connecting to Solo wifi");

        // Start connecting to solo network
        emit connect_to_solo_network();
        emit updateProgressBar(50, 30);
    } else {
        ((QStackedWidget *) this->parent())->setCurrentIndex(1);
    }
}

void WelcomeWidget::droneDetected(DroneStatus* s)
{
    setupReady();
}

void WelcomeWidget::selectedImage(int file)
{
    if(pictures.length()!=0)
    {
    QPixmap pic = QPixmap(QString(":/ui/screens/").append(pictures.at(file)));
    ui->hintView->setPixmap(pic.scaled(ui->hintView->width() - 60, ui->hintView->height(), Qt::KeepAspectRatio));
    pictureTimerCounter = (file + 1) % pictures.size();
    timer->start(30000);
    }
}

void WelcomeWidget::pictureTimer()
{
    if(pictures.length()!=0)
    {
    QPixmap pic = QPixmap(QString(":/ui/screens/").append(pictures.at(pictureTimerCounter)));
    ui->hintView->setPixmap(pic.scaled(ui->hintView->width() - 60, ui->hintView->height(), Qt::KeepAspectRatio));
    pictureTimerCounter = (pictureTimerCounter + 1) % pictures.size();
    timer->start(10000);
    }
}


void WelcomeWidget::connected_to_solo_network()
{
    // Set processBar to 50%
    pbc->aborted = true;
    pbct.wait(2);
    emit updateProgressBar(50, 1);
    pbct.wait(1000);

    // Set statusLabel
    ui->statusLabel->setText("Connected to Solo wifi");

    gd = new GatewayDialog();
    connect(gd->getButtonBox(), SIGNAL(accepted()), this, SLOT(start_set_gateway()));
    gd->open();
}

void WelcomeWidget::not_connected_to_solo_network(QString error)
{
     ui->statusLabel->setText(error);
     pbc->aborted = true;
     pbct.wait(2);
}

void WelcomeWidget::start_set_gateway()
{
    ui->statusLabel->setText("Connecting to gateway");

    QString ssid = gd->getSSID();
    QString password = gd->getPassword();
    emit set_gateway(ssid, password);
    emit updateProgressBar(100, 81);

//    // Connect to solo network and update processBar
//    QFuture<QString> result = QtConcurrent::run(this, &WelcomeWidget::set_gateway, ssid, password);
//    emit updateProgressBar(100, 10);

//    // Get result and end process
//    QString output = result.result();
//    pbc->aborted = true;
//    pbct.wait(2);
//    emit updateProgressBar(100, 1);
//    pbct.wait(1000);

//    // Set statusLabel
//    bool internet_connection;
//    if (output.contains(QRegExp("Not connected:")))
//    {
//        message = output.split(QRegExp("Not connected:"), QString::SkipEmptyParts).last();
//        connected = false;
//    } else {
//        message = "Connected to Solo wifi";
//        connected = true;
//    }
//    ui->statusLabel->setText(message);
//}

//QString WelcomeWidget::set_gateway(QString ssid, QString password)
//{
//    QProcess *process = new QProcess();
//    //process->start("/bin/bash", QStringList() << "qrc:/scripts/test");
//    process->setWorkingDirectory("../../src/scripts");
//    process->start("./set_gateway.sh " + ssid + " " + password);
//    process->waitForFinished(20000);
//    QString output(process->readAll());
//    QString result = output.split(QRegExp("[\r\n]"), QString::SkipEmptyParts).last();
//    return result;
}

void WelcomeWidget::gateway_setted()
{
    // Set processBar to 50%
    pbc->aborted = true;
    pbct.wait(2);
    emit updateProgressBar(100, 1);
    pbct.wait(1000);

    // Set statusLabel
    ui->statusLabel->setText("Connected to gateway");

    if(!droneConnected)
    {
        ui->configSearchButton->setEnabled(false);
    }

    ui->configSearchButton->setText("Configure search");
    status ++;
}

void WelcomeWidget::gateway_not_setted(QString error)
{
    ui->statusLabel->setText(error);
    pbc->aborted = true;
    pbct.wait(2);
}

void WelcomeWidget::incrementProcessBar()
{
    int value = ui->progressBar->value();
    ui->progressBar->setValue(value + 1);
}
