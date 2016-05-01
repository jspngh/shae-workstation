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
        // Create and init progressBarController
        QThread pbct;
        ProgressBarController *pbc = new ProgressBarController();
        pbc->setProgressBar(ui->progressBar);
        pbc->moveToThread(&pbct);
        QObject::connect(this, SIGNAL(updateProgressBar(int, int)), pbc, SLOT(update(int, int)));
        pbct.start();

        // Set statusLabel
        QString message = "Connecting to Solo wifi";
        ui->statusLabel->setText(message);

        // Connect to solo network and update processBar
        QFuture<QString> result = QtConcurrent::run(this, &WelcomeWidget::connect_to_solo_wifi);
        emit updateProgressBar(50, 10);

        // Get result and end process
        QString output = result.result();
        pbc->aborted = true;
        pbct.wait(2);
        emit updateProgressBar(50, 1);

        // Set statusLabel
        bool connected;
        if (output.contains(QRegExp("Not connected:")))
        {
            message = output.split(QRegExp("Not connected:"), QString::SkipEmptyParts).last();
            connected = false;
        } else {
            message = "Connected to Solo wifi";
            connected = true;
        }
        ui->statusLabel->setText(message);

        y
        ui->configSearchButton->setText("Configure Search");

        if(!droneConnected)
            ui->configSearchButton->setEnabled(false);
        status ++;
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

QString WelcomeWidget::connect_to_solo_wifi()
{
    QProcess *process = new QProcess();
    //process->start("/bin/bash", QStringList() << "qrc:/scripts/test");
    process->setWorkingDirectory("../../src/scripts");
    process->start("./connect_to_solo_network.sh");
    process->waitForFinished(-1);
    QString output(process->readAll());
    QString result = output.split(QRegExp("[\r\n]"), QString::SkipEmptyParts).last();
    return result;
}

QString WelcomeWidget::set_gateway(QString ssid, QString password)
{
    QProcess *process = new QProcess();
    //process->start("/bin/bash", QStringList() << "qrc:/scripts/test");
    process->setWorkingDirectory("../../src/scripts");
    process->start("./set_gateway.sh " + ssid + " " + password);
    process->waitForFinished(-1);
    QString output(process->readAll());
    QString result = output.split(QRegExp("[\r\n]"), QString::SkipEmptyParts).last();
    return result;
}
