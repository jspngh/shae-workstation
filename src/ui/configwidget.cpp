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
#include <QCheckBox>

ConfigWidget::ConfigWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConfigWidget)
{
    //setup UI
    ui->setupUi(this);

    ui->droneTable->setColumnWidth(CHECK, 30);
    ui->droneTable->setColumnWidth(TYPE, 100);
    ui->droneTable->setColumnWidth(BATTERY, 100);
    ui->droneTable->setColumnWidth(IP_PORT, 150);
    ui->droneTable->verticalHeader()->hide();

    ui->droneTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->droneTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->precisionSlider->setMaximum(100);

    //setup connections
    //welcomewidget
    connect(((MainWindow *) parent)->getWelcomeWidget(), SIGNAL(configFileSignal(QString)), this, SLOT(initConfScreen(QString)));
    //lowerbuttons:
    connect(ui->startButton, SIGNAL(clicked()), this, SLOT(startButtonPush()));
    connect(ui->backButton, SIGNAL(clicked()), this, SLOT(backButtonPush()));
    connect(ui->locateButton, SIGNAL(clicked()), this, SLOT(locateButtonPush()));
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
                            11,
                            true);
    connect(mapView, SIGNAL(mapFailedToLoad()),
            this, SLOT(onMapFailedToLoad()));
    connect(mapView, SIGNAL(mapLoaded()),
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
    if (event->key() == Qt::Key_Shift) {
        if (mapView != NULL)
            mapView->shiftKeyPressed(true);
    }
    QWidget::keyPressEvent(event);
}

void ConfigWidget::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Shift) {
        if (mapView != NULL)
            mapView->shiftKeyPressed(false);
    }
    QWidget::keyReleaseEvent(event);
}

void ConfigWidget::initConfScreen(QString f)
{
    QFile file(f);
    if (file.open(QIODevice::ReadOnly)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList splitLine = line.split(" ");
            if (splitLine.at(0) == "Precision:") {
                ui->PrecisionValueLabel->setText(splitLine.at(1));
                ui->precisionSlider->setValue((((QString)splitLine.at(0).split("%").at(0)).toInt()));
            } else if (splitLine.at(0) == "Search") {
                ui->searchStrategyComboBox->setCurrentText((QString) splitLine.at(2));
            } else if (splitLine.at(0) == "Location") {
                ui->locateField->setText((QString) splitLine.at(3));
            } else if (splitLine.at(0) == "Longitude") {
                ui->longitudeField->setText((QString) splitLine.at(3));
            } else if (splitLine.at(0) == "Latitude") {
                ui->latitudeField->setText((QString) splitLine.at(3));
            } else if (splitLine.at(0) == "Center") {
                mapView->setCenter(QGeoCoordinate(splitLine.at(5).toDouble(), splitLine.at(4).toDouble(), splitLine.at(6).toDouble()));
            } else if (splitLine.at(0) == "Bottom") {

            } else if (splitLine.at(0) == "Top") {

            }
        }
        file.close();
    } else {
        ui->PrecisionValueLabel->setText("0%");
        ui->precisionSlider->setValue(0);
        ui->searchStrategyComboBox->setCurrentIndex(0);
        ui->locateField->setText("0");
        ui->longitudeField->setText("0");
        ui->latitudeField->setText("0");
        mapView->setCenter(QGeoCoordinate(51.022692, 3.709853));
    }
}

void ConfigWidget::sliderChanged(int value)
{
    ui->PrecisionValueLabel->setText(QString::number(value).toStdString().append("%").c_str());
}

void ConfigWidget::setMediator(Mediator *mediator)
{
    this->mediator = mediator;

    setSignalSlots();
    emit requestDronesStatus();
}

void ConfigWidget::startButtonPush()
{
    if (mediator) {
        Search *s = new Search();
        s->setArea(mapView->selectedArea());

        QList<DroneModule *> dronesInSearch;
        for (int i = 0; i < dronesInTable.size(); i++) {
            QCheckBox *cb = (QCheckBox *)ui->droneTable->cellWidget(dronesInTable[i].first, CHECK);
            if (cb->isChecked())
                dronesInSearch.append(dronesInTable[i].second);
        }
        qDebug() << dronesInSearch.size();
        s->setDroneList(dronesInSearch);

        emit startSearch(s);
        qDebug() << "emit ConfigWidget::startSearch(Search *s)";
    }

    ((QStackedWidget *) this->parent())->setCurrentIndex(2);
}

void ConfigWidget::backButtonPush()
{
    ((QStackedWidget *) this->parent())->setCurrentIndex(0);
}

void ConfigWidget::locateButtonPush()
{
    QString choice = ui->locateComboBox->currentText();
    if (choice == "Location") {
        mapView->setCenter(ui->locateField->text());
    } else if (choice == "Coordinates") {
        mapView->setCenter(QGeoCoordinate(
            ui->latitudeField->text().toDouble(),
            ui->longitudeField->text().toDouble()
        ));
    } else {
        qWarning() << "User chose something else than \"Location\" or \"Coordinates\"";
    }
}

void ConfigWidget::setSignalSlots()
{
    mediator->addSignal(this, SIGNAL(requestDronesStatus()), QString("requestStatus()"));
    mediator->addSignal(this, SIGNAL(startSearch(Search *)), QString("startSearch(Search*)"));
    mediator->addSlot(this, SLOT(updateDroneTable(DroneStatus *)), QString("droneStatusReceived(DroneStatus*)"));
    mediator->addSlot(this, SLOT(updateMapCenter(DroneStatus *)), QString("droneStatusReceived(DroneStatus*)"));
}


void ConfigWidget::updateMapCenter(DroneStatus s)
{
    if(mapCentered) return;

    mapView->setCenter(s.getCurrentLocation());
    mapCentered = true;
}


void ConfigWidget::updateDroneTable(DroneStatus s)
{
    qDebug() << "updateDroneTable";

    DroneModule *d = s.getDrone();
    int currentRow = getDroneInTableIndex(d);

    if(currentRow == -1) {
        ui->droneTable->insertRow(ui->droneTable->rowCount());
        currentRow = ui->droneTable->rowCount() - 1;
    }

    // fill or update row
    QCheckBox *checkbox = new QCheckBox();
    ui->droneTable->setCellWidget(currentRow, CHECK, checkbox);

    // set type
    if(s.getType().isEmpty())
        ui->droneTable->setItem(currentRow, TYPE, new QTableWidgetItem(QString("Not available")));
    else
        ui->droneTable->setItem(currentRow, TYPE, new QTableWidgetItem(s.getType()));

    // set battery
    if (s.getBatteryLevel() == -1)
        ui->droneTable->setItem(currentRow, BATTERY, new QTableWidgetItem(QString("Not available")));
    else
        ui->droneTable->setItem(currentRow, BATTERY,
                                new QTableWidgetItem(QString::number(s.getBatteryLevel()) +" %"));

    // set ip and port
    QString ip_port = d->getDroneIp() + QString(':') + QString::number(d->getDronePort());
    ui->droneTable->setItem(currentRow, IP_PORT, new QTableWidgetItem(ip_port));

    dronesInTable.append(QPair<int, DroneModule *>(currentRow, d));
}

int ConfigWidget::getDroneInTableIndex(DroneModule *d)
{
    for(int i = 0; i < dronesInTable.size(); i++)
        if(dronesInTable[i].second->getGuid() == d->getGuid())
            return i;

    return -1;
}
