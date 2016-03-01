#include "welcomewidget.h"
#include "ui_welcomewidget.h"

WelcomeWidget::WelcomeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WelcomeWidget)
{
    ui->setupUi(this);

    connect(ui->pushButton,SIGNAL(clicked()),this, SLOT(nextButtonPush()));
}

WelcomeWidget::~WelcomeWidget()
{
    delete ui;
}

void WelcomeWidget::nextButtonPush(){
    ((QStackedWidget*) this->parent())->setCurrentIndex(1);
}
