#include <QDebug>
#include <QMessageBox>
#include <QDir>
#include <QPixmap>
#include <QTimer>
#include <QMessageBox>
#include "welcomewidget.h"
#include "ui_welcomewidget.h"
#include "clickablelabel.h"

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
    pictures = QDir(":/ui/screens").entryList();

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
    mediator->addSlot(this, SLOT(onDroneStatusReceived(DroneStatus*)), QString("droneStatusReceived(DroneStatus*)"));
    mediator->addSlot(this, SLOT(onDroneSetupFailure()), QString("droneSetupFailed()"));
}

void WelcomeWidget::setupReady()
{
     if(status > 0) {
         ui->configSearchButton->setEnabled(true);
     } else {
         droneConnected = true;
     }
}

void WelcomeWidget::setupFailed()
{
    if (this->status >= 0)
    {
        this->status = -1;
        QMessageBox msgBox;
        msgBox.setWindowTitle("An error occured");
        msgBox.setText("There was a problem while setting up the drone.");
        msgBox.setDetailedText("Please restart the application and the services on the drone.");
        msgBox.exec();
    }
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
        ui->configSearchButton->setText("Configure Search");
        if(!droneConnected) {
            ui->configSearchButton->setEnabled(false);
        }
        status ++;
    } else {
        ((QStackedWidget *) this->parent())->setCurrentIndex(1);
    }
}

void WelcomeWidget::onDroneStatusReceived(DroneStatus* s)
{
    setupReady();
}

void WelcomeWidget::onDroneSetupFailure()
{
    setupFailed();
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
