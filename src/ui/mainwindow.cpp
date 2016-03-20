#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QLabel>
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

    statusBar()->addWidget(new QLabel(tr("Ready")));

    qApp->setStyle("Fusion");
    QFile file(":styles/main.qss");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qApp->setStyleSheet(file.readAll());
        file.close();
    }

    connect(ui->exitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(ui->connectAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
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

