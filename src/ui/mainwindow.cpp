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
                            QGeoCoordinate(51.02, 3.73),
                            11);
    connect(mapView, SIGNAL(tilesLoaded()),
            this, SLOT(onMapLoaded()));
}

void MainWindow::onMapLoaded()
{
    ui->searchArea->replaceWidget(ui->searchAreaLoadingLabel, mapView);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Shift) {
        if(mapView != NULL)
            mapView->shiftKeyPressed(true);
    }
    QMainWindow::keyPressEvent(event);
}
void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Shift) {
        if(mapView != NULL)
            mapView->shiftKeyPressed(false);
    }
    QMainWindow::keyReleaseEvent(event);
}

