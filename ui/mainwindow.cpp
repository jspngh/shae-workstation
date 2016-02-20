#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->addPixmap(QPixmap(":/img/map.png"));
    ui->searchAreaMap->setScene(scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}

