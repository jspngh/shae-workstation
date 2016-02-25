#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initializeMap();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initializeMap()
{
    mapView = new QMMapView(QMMapView::Satellite,
                            QMCoordinate(51.02, 3.73),
                            11);
    connect(mapView, SIGNAL(tilesLoaded()),
            this, SLOT(onMapLoaded()));
}

void MainWindow::onMapLoaded()
{
    ui->searchArea->replaceWidget(ui->searchAreaLoadingLabel, mapView);
}

