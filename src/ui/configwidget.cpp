#include "configwidget.h"
#include "ui_configwidget.h"
#include <QDebug>

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
    ui->droneTable->horizontalHeader()->setStretchLastSection(true);

    ui->droneTable->verticalHeader()->hide();

    //setup connections
    connect(ui->locateButton, SIGNAL(clicked()), this, SLOT(locateButtonPush()));
    connect(ui->startButton, SIGNAL(clicked()), this, SLOT(startButtonPush()));
    connect(ui->chooseSquareButton, SIGNAL(toggled(bool)), this, SLOT(chooseSquare(bool)));
    //connect(ui->precisionSlider, SIGNAL(valueChanged(int)), this, SLOT(sliderChanged(int)));

    initializeMap();
    ui->startButton->setDisabled(false);
}

ConfigWidget::~ConfigWidget()
{
    delete ui;
}

void ConfigWidget::initializeMap()
{
    mapView = new QMMapView(QMMapView::Satellite, QGeoCoordinate(51.02, 3.73), 11);
    connect(mapView, SIGNAL(mapFailedToLoad()), this, SLOT(onMapFailedToLoad()));
    connect(mapView, SIGNAL(mapLoaded()), this, SLOT(onMapLoaded()));
    connect(mapView, SIGNAL(selectedAreaCreated(QGeoShape)), this, SLOT(areaSelected(QGeoShape)));
}

void ConfigWidget::onMapLoaded()
{
    mapView->setSelectionType(QMSelectionType::Square);
    ui->searchArea->replaceWidget(ui->searchAreaLoadingLabel, mapView);
    ui->searchAreaLoadingLabel->hide();
}

void ConfigWidget::onMapFailedToLoad()
{
    ui->searchAreaLoadingLabel->setText(QString(
                                            "Error loading map.\nPlease check your internet connection."
                                        ));
}

void ConfigWidget::areaSelected(QGeoShape area)
{
    this->areaWasSelected = true;
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
    //ui->PrecisionValueLabel->setText(QString::number(value).toStdString().append("%").c_str());
}

void ConfigWidget::chooseSquare(bool checked)
{
    if(!mapView->hasLoaded()) return;

    if(checked)
        mapView->setSelectionType(QMSelectionType::Square);
    else
        mapView->setSelectionType(QMSelectionType::Polygon);
}

void ConfigWidget::setMediator(Mediator *mediator)
{
    this->mediator = mediator;

    setSignalSlots();
    emit requestDronesStatus();
}

void ConfigWidget::startButtonPush()
{
    if(!areaWasSelected) {
        QMessageBox::warning(this, "Not too fast...","Please select an area before starting the search.", "OK");
        return;
    }

    if(mapView->selectedArea()->type() == QGeoShape::RectangleType) {
        QGeoRectangle area = *(mapView->selectedArea());
        this->areaOfArea = area.bottomLeft().distanceTo(area.bottomRight())
                            * area.bottomLeft().distanceTo(area.topLeft());
    } else {
        GeoPolygon *polygon = static_cast<GeoPolygon*>(mapView->selectedArea());
        this->areaOfArea = polygon->getArea();
        delete polygon;
    }
    qDebug() << "Selected area has size of :" << this->areaOfArea;

    if(areaOfArea > MAX_AREA_OF_AREA) {
         QMessageBox::warning(this, "Warning!", "The selected area is too big to be searched!", "OK");
         return;
    }

    if(areaOfArea < MIN_AREA_OF_AREA) {
         QMessageBox::warning(this, "Warning!", "Please select a bigger area", "OK");
         return;
    }

    QList<DroneModule *> dronesInSearch;
    for (int i = 0; i < dronesInTable.size(); i++) {
        QCheckBox *cb = (QCheckBox *)ui->droneTable->cellWidget(dronesInTable[i].first, CHECK);
        if (cb->isChecked())
            dronesInSearch.append(dronesInTable[i].second);
    }
    if(dronesInSearch.size() == 0) {
        QMessageBox::warning(this, "Not too fast...!", "Please select a drone before starting the search", "OK");
    } else if (mediator) {
        Search *s = new Search();
        s->setArea(*(mapView->selectedArea()));
        s->setHeight(ui->heightDoubleSpinBox->value());
        s->setFpsProcessing(ui->fpsSpinBox->value());
        s->setGimbalAngle(ui->cameraAngleDoubleSpinBox->value());
        s->setSpeed(ui->speedDoubleSpinBox->value());
        s->setDroneList(dronesInSearch);

        qDebug() << "emit ConfigWidget::startSearch(Search *s)";
        emit startSearch(s);

        ((QStackedWidget *) this->parent())->setCurrentIndex(2);
    }
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
    mediator->addSlot(this, SLOT(updateDroneTable(DroneStatus *)), QString("droneStatusReceived(DroneStatus*)"));
    mediator->addSlot(this, SLOT(updateMapCenter(DroneStatus *)), QString("droneStatusReceived(DroneStatus*)"));
}

void ConfigWidget::updateMapCenter(DroneStatus* heartbeat)
{
    if (!mapView->hasLoaded()) return;

    // position drone on map
    QGeoCoordinate center = heartbeat->getCurrentLocation();
    QString id = heartbeat->getDrone()->getGuid().toString();
    if (mapView->hasMarker(id)) {
        QMMarker &marker = mapView->getMarker(id);
        marker.setOrientation(qRadiansToDegrees(heartbeat->getOrientation()));
        marker.moveTo(center);
    } else {
        QMMarker &marker = mapView->addMarker(id, center);
        marker.setIcon("qrc:///ui/icons/drone");
        marker.scale(0.1, 0.1);
        marker.setOrientation(qRadiansToDegrees(heartbeat->getOrientation()));
        marker.show();
    }

    // only center the map once
    if (!mapCentered) {
        mapView->setCenter(center);
        mapView->setZoomLevel(11);
        mapCentered = true;
    }
}

void ConfigWidget::updateDroneTable(DroneStatus* s)
{
    qDebug() << "updateDroneTable";

    DroneModule *d = s->getDrone();
    int currentRow = getDroneInTableIndex(d);

    if (currentRow == -1) {
        ui->droneTable->insertRow(ui->droneTable->rowCount());
        currentRow = ui->droneTable->rowCount() - 1;
    }

    // fill or update row
    QCheckBox *checkbox = new QCheckBox();
    ui->droneTable->setCellWidget(currentRow, CHECK, checkbox);

    // set type
    if (s->getType().isEmpty()) {
        QTableWidgetItem* item = new QTableWidgetItem(QString("Not available"));
        item->setTextAlignment(Qt::AlignCenter);
        ui->droneTable->setItem(currentRow, TYPE, item);
    } else {
        QTableWidgetItem* item = new QTableWidgetItem(s->getType());
        item->setTextAlignment(Qt::AlignCenter);
        ui->droneTable->setItem(currentRow, TYPE, item);
    }

    // set battery
    if (s->getBatteryLevel() == -1) {
        QTableWidgetItem* item = new QTableWidgetItem(QString("Not available"));
        item->setTextAlignment(Qt::AlignCenter);
        ui->droneTable->setItem(currentRow, BATTERY, item);
    } else {
        QTableWidgetItem* item = new QTableWidgetItem(QString::number(s->getBatteryLevel()) + " %");
        item->setTextAlignment(Qt::AlignCenter);
        ui->droneTable->setItem(currentRow, BATTERY, item);
    }

    // set ip and port
    QString ip_port = d->getDroneIp() + QString(':') + QString::number(d->getDronePort());
    QTableWidgetItem* item = new QTableWidgetItem(ip_port);
    item->setTextAlignment(Qt::AlignCenter);
    ui->droneTable->setItem(currentRow, IP_PORT, item);

    dronesInTable.append(QPair<int, DroneModule *>(currentRow, d));
}

int ConfigWidget::getDroneInTableIndex(DroneModule *d)
{
    for (int i = 0; i < dronesInTable.size(); i++)
        if (dronesInTable[i].second->getGuid() == d->getGuid())
            return i;

    return -1;
}

