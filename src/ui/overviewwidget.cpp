#include "overviewwidget.h"
#include "ui_overviewwidget.h"

OverviewWidget::OverviewWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OverviewWidget)
{
    ui->setupUi(this);
    mapViewLoaded = false;

    //lowerbuttons:
    connect(ui->exportSearchButton, SIGNAL(clicked()), this, SLOT(exportSearchButtonPush()));
}

OverviewWidget::~OverviewWidget()
{
    delete ui;
}

void OverviewWidget::setMediator(Mediator *mediator)
{
    this->mediator = mediator;
    mediator->addSlot(this, SLOT(onSearchStarted(Search *)), QString("startSearch(Search*)"));
    mediator->addSlot(this, SLOT(onHeartBeatReceived(DroneStatus)), QString("droneHeartBeatReceived(DroneStatus)"));
    mediator->addSlot(this, SLOT(updateDroneList(DroneStatus)), QString("droneStatusReceived(DroneStatus)"));
}

void OverviewWidget::onHeartBeatReceived(DroneStatus heartbeat)
{
    if(!mapViewLoaded) return;
    ui->heartBeat->setText(heartbeat.toString());

    QString id = heartbeat.getDrone()->getGuid().toString();
    if(mapView->hasMarker(id)) {
        QMMarker& marker = mapView->getMarker(id);
        marker.moveTo(heartbeat.getCurrentLocation());
    } else {
        QMMarker& marker = mapView->addMarker(id, heartbeat.getCurrentLocation());
        marker.setIcon("qrc:///ui/img/map/drone-icon");
        marker.scale(0.5, 0.5);
        /* marker.rotate(20); */
        marker.show();
    }
}

void OverviewWidget::exportSearchButtonPush()
{
}

void OverviewWidget::updateDroneList(DroneStatus s)
{
    const QUuid droneId = s.getDrone()->getGuid();
    if(mapIdListItem.contains(droneId))
        mapIdListItem.value(droneId)->updateStatus(s);
}

void OverviewWidget::onSearchStarted(Search *s)
{
    this->search = s;
    mapView = new QMMapView(QMMapView::Satellite,
                            s->getArea().center(),
                            11,
                            false);

    connect(mapView, SIGNAL(mapFailedToLoad()),
            this, SLOT(onMapFailedToLoad()));
    connect(mapView, SIGNAL(mapLoaded()),
            this, SLOT(onMapLoaded()));

    fillDroneList();
}

void OverviewWidget::fillDroneList()
{
    uint i = 1;
    Q_FOREACH(DroneModule *drone, search->getDroneList()) {
        QListWidgetItem *item = new QListWidgetItem();
        item->setSizeHint(QSize(0, 150));
        ui->droneList->addItem(item);

        OverviewDroneItem *droneItem = new OverviewDroneItem(drone, i);
        mapIdListItem[drone->getGuid()] = droneItem;
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

