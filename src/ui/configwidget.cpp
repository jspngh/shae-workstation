#include "configwidget.h"
#include "ui_configwidget.h"
#include <QDebug>

ConfigWidget::ConfigWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConfigWidget),
    timerStatusesRequest(new QTimer())
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
    initTimers();
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
    connect(mapView, SIGNAL(selectedAreaCreated()), this, SLOT(areaSelected()));
    connect(mapView, SIGNAL(selectedAreaDeleted()), this, SLOT(areaDeleted()));
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

void ConfigWidget::areaSelected()
{
    this->areaWasSelected = true;
}

void ConfigWidget::areaDeleted()
{
    this->areaWasSelected = false;
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

    mapView->removeAllSelections();
    if(checked)
        mapView->setSelectionType(QMSelectionType::Square);
    else
        mapView->setSelectionType(QMSelectionType::Polygon);
}

void ConfigWidget::setMediator(Mediator *mediator)
{
    this->mediator = mediator;

    setSignalSlots();
}

void ConfigWidget::startButtonPush()
{
    if(!areaWasSelected){
        QMessageBox::warning(this, "Not too fast...","Please select an area before starting the search.", "OK");
        return;
    }

    QGeoCoordinate center;
    if(mapView->selectedArea()->type() == QGeoShape::RectangleType) {
        QGeoRectangle* area = static_cast<QGeoRectangle*>(mapView->selectedArea());
        this->areaOfArea = area->bottomLeft().distanceTo(area->bottomRight())
                            * area->bottomLeft().distanceTo(area->topLeft());
        center = area->center();
    } else {
        GeoPolygon *polygon = static_cast<GeoPolygon*>(mapView->selectedArea());
        this->areaOfArea = polygon->getArea();
        center = polygon->center();
        if(!polygon->isValid()) {
            QMessageBox::warning(this, "Warning!", "The selected polygon is not convex!", "OK");
            delete polygon;
            return;
        }
        delete polygon;
    }

    if(areaOfArea > MAX_AREA_OF_AREA) {
        QString messageFormat = QString("The selected area is too big to be searched.\nThe area is %1 m² while the max. area allowed is %2 m².");
        QString message = messageFormat.arg(areaOfArea, 0, 'f', 2).arg(MAX_AREA_OF_AREA);
        QMessageBox::warning(this, "Warning: selected area too big!", message, "OK");
        return;
    }

    if(areaOfArea < MIN_AREA_OF_AREA) {
        QString messageFormat = QString("The selected area is too small to be searched.\nThe area is %1 m² while the min. area allowed is %2 m².");
        QString message = messageFormat.arg(areaOfArea, 0, 'f', 2).arg(MIN_AREA_OF_AREA);
        QMessageBox::warning(this, "Warning: selected area too small!", message, "OK");
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
        return;
    }

    double distanceToArea = center.distanceTo(dronesInSearch.front()->getLastReceivedDroneStatus().getCurrentLocation());
    if(distanceToArea > MAX_DISTANCE) {
        QString messageFormat = QString("The area selected is too far away %1 for the drone to fly to (max. distance is %2).");
        QString message = messageFormat.arg(distanceToArea, 0, 'f', 2).arg(MAX_DISTANCE);
        QMessageBox::warning(this, "Warning!", message, "OK");
        return;
    }

    qDebug() << "Selected area has size of :" << this->areaOfArea;
    qDebug() << "Center of selected area is: " << center;
    qDebug() << "Drone's home location is: " << dronesInSearch.front()->getLastReceivedDroneStatus().getCurrentLocation();
    qDebug() << "Distance to selected area is: " << distanceToArea;
    if (mediator) {
        Search *s = new Search();
        s->setArea(mapView->selectedArea());
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
    qDebug() << "adding slots";
    mediator->addSignal(this, SIGNAL(requestDronesStatus()), QString("requestStatus()"));
    mediator->addSignal(this, SIGNAL(startSearch(Search *)), QString("startSearch(Search*)"));
    mediator->addSlot(this, SLOT(onStartSearch(Search *)), QString("startSearch(Search*)"));
    mediator->addSlot(this, SLOT(updateDroneTable(DroneStatus *)), QString("droneStatusReceived(DroneStatus*)"));
    mediator->addSlot(this, SLOT(updateMapCenter(DroneStatus *)), QString("droneStatusReceived(DroneStatus*)"));
}

void ConfigWidget::onStartSearch(Search *search)
{
    timerStatusesRequest->stop();
}

void ConfigWidget::updateMapCenter(DroneStatus* heartbeat)
{
    if (mapView == nullptr || !mapView->hasLoaded()) return;

    // position drone on map
    QString id = heartbeat->getDrone()->getGuid().toString();

    if (mapView->hasMarker(id)) {
        // only move the center of the map if the drone has moved a large enough distance
        if(mapCentered && center.distanceTo(heartbeat->getCurrentLocation()) > 2) {
            center = heartbeat->getCurrentLocation();
            QMMarker &marker = mapView->getMarker(id);
            marker.setOrientation(qRadiansToDegrees(heartbeat->getOrientation()));
            marker.moveTo(center);
        }
    } else {
        center = heartbeat->getCurrentLocation();
        QMMarker &marker = mapView->addMarker(id, center);
        marker.setIcon("qrc:///ui/icons/drone");
        marker.scale(0.1, 0.1);
        marker.setOrientation(qRadiansToDegrees(heartbeat->getOrientation()));
        marker.show();
    }

    // only center the map once
    if (!mapCentered) {
        mapView->setCenter(center);
        mapView->setZoomLevel(18);
        mapCentered = true;
    }
}

void ConfigWidget::updateDroneTable(DroneStatus* s)
{
    DroneModule *d = s->getDrone();
    int currentRow = getDroneInTableIndex(d);

    if (currentRow == -1) {
        ui->droneTable->insertRow(ui->droneTable->rowCount());
        currentRow = ui->droneTable->rowCount() - 1;

        // create checkbox in the first element of the row
        QCheckBox *checkbox = new QCheckBox();
        ui->droneTable->setCellWidget(currentRow, CHECK, checkbox);

        // store the dronemodule and it corresponding row in the table
        dronesInTable.append(QPair<int, DroneModule *>(currentRow, d));
    }

    // fill or update row

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



    if(!timerStatusesRequest->isActive())
    {
        qDebug() << "start the timer";
        timerStatusesRequest->start();
    }
}

int ConfigWidget::getDroneInTableIndex(DroneModule *d)
{
    for (int i = 0; i < dronesInTable.size(); i++){
        if (dronesInTable[i].second->getGuid() == d->getGuid())
            return i;
    }

    return -1;
}

void ConfigWidget::initTimers()
{
    timerStatusesRequest->setInterval(3000);
    connect(timerStatusesRequest, SIGNAL(timeout()), this, SLOT(requestStatuses()));
}

void ConfigWidget::requestStatuses()
{
    for(int i=0; i < dronesInTable.size(); i++){
        dronesInTable[i].second->requestStatus();
        qDebug() << "requesting drone statuses";
    }
}

