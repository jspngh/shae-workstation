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

#include "core/controller.h"

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

void ConfigWidget::setController(Controller *value)
{
    controller = value;
    // now that the controller is set, some extra initialization is necessary
    setSignalSlots();
    fillDroneTable();
}

void ConfigWidget::startButtonPush()
{
    if (controller) {
        Search *s = controller->getSearch();

        // TODO: read the search area from the gui
        QGeoRectangle area(QGeoCoordinate(51.022960, 3.709623), QGeoCoordinate(51.022761, 3.709877));
        s->setArea(area);

        QList<DroneModule *> *dronesInSearch = new QList<DroneModule *>();
        for (int i = 0; i < dronesInTable.size(); i++) {
            QCheckBox *cb = (QCheckBox *)ui->droneTable->cellWidget(dronesInTable[i].first, CHECK);
            if (cb->isChecked())
                dronesInSearch->append(dronesInTable[i].second);
        }
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
        //herpaderp, this shouldn't happen
    }
}

void ConfigWidget::setSignalSlots()
{
    controller->getMediator()->addSignal(this, SIGNAL(startSearch(Search *)), QString("startSearch(Search*)"));
    controller->getMediator()->addSlot(this, SLOT(updateDroneTable(DroneStatus)), QString("droneStatusReceived(DroneStatus)"));
}

void ConfigWidget::fillDroneTable()
{
    ui->droneTable->clearContents();
    for (int row = 0; row < controller->getDrones()->size(); row++) {
        DroneModule *d = (*(controller->getDrones()))[row];
        QString ip_port = d->getServerIp() + QString(':') + QString::number(d->getPortNr());
        ui->droneTable->insertRow(ui->droneTable->rowCount());
        int currentRow = ui->droneTable->rowCount() - 1;

        // fill newly created row
        QCheckBox *checkbox = new QCheckBox();
        ui->droneTable->setCellWidget(currentRow, CHECK, checkbox);
        ui->droneTable->setItem(currentRow, TYPE, new QTableWidgetItem(QString("Solo 3DR")));
        ui->droneTable->setItem(currentRow, BATTERY, new QTableWidgetItem(QString("33 %")));
        ui->droneTable->setItem(currentRow, IP_PORT, new QTableWidgetItem(ip_port));

        dronesInTable.append(QPair<int, DroneModule *>(row, d));

        d->requestStatus();
    }
}

void ConfigWidget::updateDroneTable(DroneStatus s)
{
    // for now we only need to update the battery levels in the drone table
    // if the battery level is not set in the status we don't update anything
    if (s.getBatteryLevel() == -1) return;

    for (int i = 0; i < dronesInTable.size(); i++) {
        if (dronesInTable[i].second->getGuid() == s.getDrone()->getGuid()) {
            QString batteryLevel = QString::number(s.getBatteryLevel()) + " %";
            ui->droneTable->setItem(i, BATTERY, new QTableWidgetItem(batteryLevel));
        }
    }
}


