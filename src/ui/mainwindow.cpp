#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	welcome_widget = new WelcomeWidget(this);
	config_widget = new ConfigWidget(this);
	overview_widget = new OverviewWidget(this);

	ui->stackedWidget->addWidget(welcome_widget);
	ui->stackedWidget->addWidget(config_widget);
	ui->stackedWidget->addWidget(overview_widget);

	ui->stackedWidget->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
	delete welcome_widget;
	delete config_widget;
	delete overview_widget;
	delete ui;
}

QWidget *MainWindow::getWelcomeWidget()
{
	return welcome_widget;
}

