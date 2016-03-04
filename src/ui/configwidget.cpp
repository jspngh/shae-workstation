#include "configwidget.h"
#include "ui_configwidget.h"
#include "mainwindow.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <sstream>
#include <QGeoRectangle>
#include <QDebug>

ConfigWidget::ConfigWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConfigWidget)
{
    //setup UI
    ui->setupUi(this);
    ui->droneTable->setColumnWidth(0,35);
    ui->droneTable->setColumnWidth(1,110);
    ui->droneTable->setColumnWidth(2,110);
    ui->droneTable->setColumnWidth(3,50);
    ui->droneTable->setColumnWidth(4,40);
    ui->precisionSlider->setMaximum(100);

    //setup connections
    //welcomewidget
    connect(((MainWindow*) parent)->getWelcomeWidget(),SIGNAL(configFileSignal(QString)),this,SLOT(initConfScreen(QString)));
    //lowerbuttons:
    connect(ui->startButton,SIGNAL(clicked()),this, SLOT(startButtonPush()));
    connect(ui->backButton,SIGNAL(clicked()),this, SLOT(backButtonPush()));
    connect(ui->locateButton,SIGNAL(clicked()),this, SLOT(locateButtonPush()));
    //slider
    connect(ui->precisionSlider, SIGNAL(valueChanged(int)), this, SLOT(sliderChanged(int)));

    initializeMap();
}

ConfigWidget::~ConfigWidget()
{
    delete ui;
}

void ConfigWidget::initializeMap()
{
    mapView = new QMMapView(QMMapView::Satellite,
                            QGeoCoordinate(51.02, 3.73),
                            11);
    connect(mapView, SIGNAL(mapFailedToLoad()),
            this, SLOT(onMapFailedToLoad()));
    connect(mapView, SIGNAL(tilesLoaded()),
            this, SLOT(onMapLoaded()));
}

void ConfigWidget::onMapLoaded()
{
    ui->searchArea->replaceWidget(ui->searchAreaLoadingLabel, mapView);
    ui->searchAreaLoadingLabel->hide();
}

void ConfigWidget::onMapFailedToLoad()
{
    ui->searchAreaLoadingLabel->setText(QString(
        "Error loading map.\nPlease check your internet connection."
    ));
}

void ConfigWidget::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Shift) {
        if(mapView != NULL)
            mapView->shiftKeyPressed(true);
    }
    QWidget::keyPressEvent(event);
}

void ConfigWidget::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Shift) {
        if(mapView != NULL)
            mapView->shiftKeyPressed(false);
    }
    QWidget::keyReleaseEvent(event);
}

void ConfigWidget::initConfScreen(QString f){
    QFile file(f);
    if (file.open(QIODevice::ReadOnly))
    {
       QTextStream in(&file);
       while (!in.atEnd())
       {
          QString line = in.readLine();
          QStringList splitLine = line.split(" ");
          for(int i = 0; i < splitLine.size(); i++){
              if(splitLine.at(i) == "Precision:")
              {
                  ui->PrecisionValueLabel->setText(splitLine.at(i+1));
                  ui->precisionSlider->setValue((((QString)splitLine.at(i+1).split("%").at(0)).toInt()));
                  break;
              }
          }
       }
       file.close();
    }
}

void ConfigWidget::sliderChanged(int value){
    ui->PrecisionValueLabel->setText(QString::number(value).toStdString().append("%").c_str());
}

void ConfigWidget::startButtonPush(){
    time_t t = time(0);
    struct tm * now = localtime(&t);
    int sec = now ->tm_sec;
    int min = now->tm_min;
    int hour = now->tm_hour;
    int day = now->tm_mday;
    int month = now->tm_mon + 1;
    int year = now->tm_year + 1900;

    std::ostringstream ss;
    ss << "search-" << sec << "-" << min << "-" << hour << "-" << day << "-" << month << "-" << year << ".conf";


    std::ofstream outfile(ss.str().c_str());

    if(ui->searchStrategyComboBox->currentText() != NULL)
    {
        outfile << "Search strategy: " << ui->searchStrategyComboBox->currentText().toStdString() << std::endl;
    }

    outfile << "Precision: " << ui->PrecisionValueLabel->text().toStdString() << std::endl;


    outfile << "TODO drone list to string" << std::endl;
    //for(QTableWidgetItem i : ui->droneTable->items()){
    //    if(false)
    //    {
            //todo implement items
    //    }
    //}

    if(mapView->region().bottomLeft().longitude() != NULL)
    {
        outfile << "Selected region coorindates: " << std::endl;
        outfile << "Bottom left: " << mapView->region().bottomLeft().toString().toStdString() << std::endl;
        outfile << "Bottom right: " << mapView->region().bottomRight().toString().toStdString() << std::endl;
        outfile << "Top left: " << mapView->region().topLeft().toString().toStdString() << std::endl;
        outfile << "Top right: " << mapView->region().topRight().toString().toStdString() << std::endl;
    }

    outfile.close();

    ((QStackedWidget*) this->parent())->setCurrentIndex(2);
}

void ConfigWidget::backButtonPush(){
    ((QStackedWidget*) this->parent())->setCurrentIndex(0);
}

void ConfigWidget::locateButtonPush(){
    QString choice = ui->locateComboBox->currentText();
    if(choice == "Location") {
        mapView->setCenter(ui->locateField->text());
    } else if(choice == "Coordinates") {
        mapView->setCenter(QGeoCoordinate(
            ui->latitudeField->text().toDouble(),
            ui->longitudeField->text().toDouble()
        ));
    } else {
        //herpaderp, this shouldn't happen
    }
}

