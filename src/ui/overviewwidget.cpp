#include "overviewwidget.h"
#include "ui_overviewwidget.h"
#include <QDebug>
#include <QFileDialog>

OverviewWidget::OverviewWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OverviewWidget)
{
    ui->setupUi(this);
    mapViewLoaded = false;
    summaryDialog = new SummaryDialog();
    summaryDialog->setWindowTitle("Search Summary");
}

OverviewWidget::~OverviewWidget()
{
    delete ui;
}

void OverviewWidget::setMediator(Mediator *mediator)
{
    this->mediator = mediator;
    summaryDialog->setMediator(mediator);
    mediator->addSlot(this, SLOT(onSearchStarted(Search *)), QString("startSearch(Search*)"));
    mediator->addSlot(this, SLOT(onHeartBeatReceived(DroneStatus *)), QString("droneHeartBeatReceived(DroneStatus*)"));
    mediator->addSlot(this, SLOT(updateDroneList(DroneStatus *)), QString("droneStatusReceived(DroneStatus*)"));
    mediator->addSlot(this, SLOT(onNewDetection(QUuid, DetectionResult*)), QString("newDetection(QUuid, DetectionResult*)"));
    mediator->addSlot(this, SLOT(onDroneLanded(DroneModule *)), QString("landed(DroneModule*)"));

}

void OverviewWidget::onHeartBeatReceived(DroneStatus *heartbeat)
{

    if (!mapViewLoaded) return;

    QUuid uuid = heartbeat->getDrone()->getGuid("OverviewWidget::onHeartBeatReceived").toString();

    // Update bottom text
    ui->heartBeat->setText(heartbeat->toString());

    // Update drone list
    OverviewDroneItem *droneItem = mapIdListItem.value(uuid);
    droneItem->setBatteryLevel(heartbeat->getBatteryLevel());

    // Update map
    if (mapView->hasMarker(uuid.toString())) {
        QMMarker &marker = mapView->getMarker(uuid.toString());
        marker.setOrientation(qRadiansToDegrees(heartbeat->getOrientation()));
        marker.moveTo(heartbeat->getCurrentLocation());
    } else {
        QMMarker &marker = mapView->addMarker(uuid.toString(), heartbeat->getCurrentLocation());
        marker.setIcon("qrc:///ui/icons/drone");
        marker.scale(0.1, 0.1);
        marker.setOrientation(qRadiansToDegrees(heartbeat->getOrientation()));
        marker.trackPath();
        marker.show();
    }

    // Update drone list
    updateDroneList(heartbeat);
}

void OverviewWidget::onNewDetection(QUuid droneId, DetectionResult* result)
{
    if(!mapIdListItem.contains(droneId))
        qWarning() << "WARNING: detection from drone " << droneId.toString();

    OverviewDroneItem *droneItem = mapIdListItem.value(droneId);

    // Update sidebar
    searchDetails->incrementPeopleLocated();
    droneItem->incrementPeopleLocated();

    // Update map
    QString markerId = droneId.toString() + "-" + QString::number(droneItem->getPeopleLocated());
    QMMarker& marker = mapView->addMarker(markerId, result->getLocation());

    marker.setIcon("qrc:///ui/icons/human");
    marker.scale(0.1*result->getScore()/100, 0.1*result->getScore()/100);
    marker.show();
}


void OverviewWidget::updateDroneList(DroneStatus *s)
{
    const QUuid droneId = s->getDrone()->getGuid("OverviewWidget::updateDroneList");
    if(mapIdListItem.contains(droneId))
        mapIdListItem.value(droneId)->updateStatus(*s);
}

void OverviewWidget::onSearchStarted(Search *s)
{
    this->search = s;

    // Initialize map
    mapView = new QMMapView(QMMapView::Satellite,
                            s->getArea().center(),
                            11,
                            false);

    connect(mapView, SIGNAL(mapFailedToLoad()),
            this, SLOT(onMapFailedToLoad()));
    connect(mapView, SIGNAL(mapLoaded()),
            this, SLOT(onMapLoaded()));

    // Show search details
    searchDetails = new OverviewSearchItem(s, this);
    ui->sidebar->insertWidget(0, searchDetails);

    // Fill list drones
    fillDroneList();
}

void OverviewWidget::fillDroneList()
{
    uint i = 1;
    Q_FOREACH (DroneModule *drone, search->getDroneList()) {
        QListWidgetItem *item = new QListWidgetItem();
        item->setSizeHint(QSize(0, 170));
        ui->droneList->addItem(item);

        OverviewDroneItem *droneItem = new OverviewDroneItem(drone, i);
        mapIdListItem[drone->getGuid("OverviewWidget::fillDroneList")] = droneItem;
        ui->droneList->setItemWidget(item, droneItem);
        i++;
    }
}

void OverviewWidget::onMapLoaded()
{
    mapView->fitRegion(search->getArea());
    mapViewLoaded = true;

    ui->mainLayout->replaceWidget(ui->mapLoadingLabel, mapView);
    ui->mapLoadingLabel->hide();
}

void OverviewWidget::onMapFailedToLoad()
{
    ui->mapLoadingLabel->setText(QString(
                                     "Error loading map.\nPlease check your internet connection."
                                 ));
}

void OverviewWidget::onDroneLanded(DroneModule *drone)
{
    // TODO check if all the drones are landed, then show the summary dialog
    summaryDialog->show();
}

