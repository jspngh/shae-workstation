#include "welcomewidget.h"
#include "ui_welcomewidget.h"

WelcomeWidget::WelcomeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WelcomeWidget)
{
    ui->setupUi(this);

    ui->progressBar->setRange(0, 0);
    // ui->configSearchButton->setEnabled(false);

    ui->configSearchButton->setCheckable(false);
}

WelcomeWidget::~WelcomeWidget()
{
    delete ui;
}


void WelcomeWidget::on_configSearchButton_clicked()
{
    ((QStackedWidget *) this->parent())->setCurrentIndex(1);
}
