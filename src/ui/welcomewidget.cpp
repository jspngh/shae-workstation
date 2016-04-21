#include "welcomewidget.h"
#include "ui_welcomewidget.h"

WelcomeWidget::WelcomeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WelcomeWidget)
{
    ui->setupUi(this);

    ui->progressBar->setRange(0, 0);
    ui->configSearchButton->setEnabled(false);
}

WelcomeWidget::~WelcomeWidget()
{
    delete ui;
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

/*************
 *  SLOTS
 * **********/

void WelcomeWidget::on_configSearchButton_clicked()
{
    ((QStackedWidget *) this->parent())->setCurrentIndex(1);
}

void WelcomeWidget::droneDetected(DroneStatus* s)
{
    setupReady();
}
