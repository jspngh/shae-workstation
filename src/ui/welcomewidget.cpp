#include "welcomewidget.h"
#include "ui_welcomewidget.h"
#include "clickablelabel.h"
#include <QDebug>
#include <QDir>
#include <QPixmap>
#include <QTimer>

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
     ui->configSearchButton->setEnabled(true);
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
