#include "configwidget.h"
#include "ui_configwidget.h"
#include <QGeoRectangle>
#include <QDebug>
#include <QCheckBox>

ConfigWidget::ConfigWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConfigWidget)
{
    this->areaWasSelected = false;

    //setup UI
    ui->setupUi(this);

    ui->droneTable->setColumnWidth(CHECK, 30);
    ui->droneTable->setColumnWidth(TYPE, 100);
    ui->droneTable->setColumnWidth(BATTERY, 100);
    ui->droneTable->setColumnWidth(IP_PORT, 150);
    ui->droneTable->verticalHeader()->hide();

    //setup connections
    connect(ui->locateButton, SIGNAL(clicked()), this, SLOT(locateButtonPush()));
    connect(ui->startButton, SIGNAL(clicked()), this, SLOT(startButtonPush()));
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
    connect(mapView, SIGNAL(selectedAreaCreated(QGeoRectangle)),
            this, SLOT(areaSelected()));
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

void ConfigWidget::areaSelected()
{
    this->areaWasSelected = true;
    ui->startButton->setDisabled(false);
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

void ConfigWidget::locateButtonPush()
{
    if (ui->chooseLocationButton->isChecked()) {
        mapView->setCenter(ui->locateField->text());
    } else {
        mapView->setCenter(QGeoCoordinate(
            ui->latitudeField->text().toDouble(),
            ui->longitudeField->text().toDouble()
        ));
    }
}

void ConfigWidget::setSignalSlots()
{
    mediator->addSignal(this, SIGNAL(requestDronesStatus()), QString("requestStatus()"));
    mediator->addSignal(this, SIGNAL(startSearch(Search *)), QString("startSearch(Search*)"));
    mediator->addSlot(this, SLOT(updateDroneTable(DroneStatus)), QString("droneStatusReceived(DroneStatus)"));
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

