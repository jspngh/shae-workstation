#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QStyleFactory>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    welcomeWidget = new WelcomeWidget(this);
    configWidget = new ConfigWidget(this);
    overviewWidget = new OverviewWidget(this);
    ui->stackedWidget->addWidget(welcomeWidget);
    ui->stackedWidget->addWidget(configWidget);
    ui->stackedWidget->addWidget(overviewWidget);

    ui->stackedWidget->setCurrentIndex(0);

    qApp->setStyle("Fusion");
    QFile file(":/ui/styles/main");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qApp->setStyleSheet(file.readAll());
        file.close();
    }
    connect(ui->exitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(ui->exportResultsButton, SIGNAL(triggered()), this, SLOT(onSaveSearchClicked()));
    connect(ui->exportFootageButton, SIGNAL(triggered()), this, SLOT(onSaveFootageClicked()));

    ui->exportFootageButton->setEnabled(true);
    ui->exportFootageButton->setEnabled(true);
}

MainWindow::~MainWindow()
{
    delete welcomeWidget;
    delete configWidget;
    delete overviewWidget;
    delete ui;
}

void MainWindow::setMediator(Mediator* mediator)
{
    this->mediator = mediator;
    mediator->addSignal(ui->resetAction, SIGNAL(triggered()), QString("resetServicesClicked()"));

    configWidget->setMediator(mediator);
    welcomeWidget->setMediator(mediator);
    overviewWidget->setMediator(mediator);
}

WelcomeWidget *MainWindow::getWelcomeWidget()
{
    return welcomeWidget;
}

ConfigWidget *MainWindow::getConfigWidget()
{
    return configWidget;
}

OverviewWidget *MainWindow::getOverviewWidget()
{
    return overviewWidget;
}

void MainWindow::onSaveSearchClicked()
{
    overviewWidget->getSummaryDialog()->onSaveSearchClicked();
}

void MainWindow::onSaveFootageClicked()
{
    overviewWidget->getSummaryDialog()->onSaveFootageClicked();
}
