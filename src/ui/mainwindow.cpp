#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mapView = new QMMapView(QMMapView::RoadMap,
                            QMCoordinate(51.02, 3.73),
                            11);
    ui->searchArea->addWidget(mapView, 2);
}

MainWindow::~MainWindow()
{
    delete ui;
}

