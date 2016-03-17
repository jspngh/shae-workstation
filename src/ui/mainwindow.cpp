#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QLabel>

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
}

MainWindow::~MainWindow()
{
    delete welcomeWidget;
    delete configWidget;
    delete overviewWidget;
    delete ui;
}

WelcomeWidget* MainWindow::getWelcomeWidget()
{
    return welcomeWidget;
}

ConfigWidget* MainWindow::getConfigWidget()
{
    return configWidget;
}

OverviewWidget* MainWindow::getOverviewWidget()
{
    return overviewWidget;
}

