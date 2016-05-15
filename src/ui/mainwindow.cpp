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

    //configure reset that needs to run in different thread
    resetCtrl = new ResetScriptController();
    resetThread = new QThread();
    resetCtrl->moveToThread(resetThread);
    connect(ui->resetAction, SIGNAL(triggered()), resetCtrl, SLOT(reset()));
    connect(resetCtrl, SIGNAL(resetSuccessful()), this, SLOT(onResetSuccessful()));
    resetThread->start();
    msgBox.setText("The drone services are resetting.");

    connect(ui->exitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(ui->exportResultsButton, SIGNAL(triggered()), this, SLOT(onSaveSearchClicked()));
    connect(ui->exportFootageButton, SIGNAL(triggered()), this, SLOT(onSaveFootageClicked()));
    connect(ui->resetAction, SIGNAL(triggered()), this, SLOT(onResetDroneClicked()));

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

void MainWindow::onResetDroneClicked()
{
    msgBox.exec();
}

void MainWindow::onResetSuccessful()
{
    msgBox.close();
}
