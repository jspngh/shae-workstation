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

//    qApp->setStyle(QStyleFactory::create("Fusion"));
    qApp->setStyle("Fusion");

    QPalette darkPalette;
    darkPalette.setColor(QPalette::Window, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::WindowText, Qt::white);
    darkPalette.setColor(QPalette::Base, QColor(25, 25, 25));
    darkPalette.setColor(QPalette::AlternateBase, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
    darkPalette.setColor(QPalette::ToolTipText, Qt::white);
    darkPalette.setColor(QPalette::Text, Qt::white);
    darkPalette.setColor(QPalette::Button, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::ButtonText, Qt::white);
    darkPalette.setColor(QPalette::BrightText, Qt::red);
    darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));

    darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::HighlightedText, Qt::black);

    qApp->setStyle("Fusion");
    QFile file(":/ui/styles/main");
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

