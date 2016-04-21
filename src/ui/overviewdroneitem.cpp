#include "overviewdroneitem.h"
#include "ui_overviewdroneitem.h"

OverviewDroneItem::OverviewDroneItem(DroneModule *drone, uint number, QWidget *parent)
    : QWidget(parent),
      ui(new Ui::OverviewDroneItem),
      locatedPeople(0),
      searchedArea(0.0),
      hasLocation(false),
      visionWidthMeters(0.0),
      visionWidthDegrees(drone->getVisionWidth())
{
    ui->setupUi(this);

    setDroneNr(number);

    // init timer
    timer->setInterval(1000);
    connect(timer, SIGNAL(timeout()), this, SLOT(checkConnectivity()));

    connect(ui->emergencyButton, SIGNAL(clicked()), drone, SLOT(emergencyLanding()));
    connect(ui->haltButton, SIGNAL(clicked()), drone, SLOT(stopFlight()));
    connect(ui->returnHomeButton, SIGNAL(clicked()), drone, SLOT(returnToHome()));
}

OverviewDroneItem::~OverviewDroneItem()
{
    delete ui;
}

void OverviewDroneItem::setDroneNr(uint number)
{
    ui->header->setText(
        QString("Drone #%1").arg(number)
    );
}

void OverviewDroneItem::setBatteryLevel(double level)
{
    ui->batteryValue->setText(
        QString("%1 %").arg(level)
    );
}

void OverviewDroneItem::setSearchedArea(double area)
{
    ui->searchAreaValue->setText(
        QString("%1 m²").arg(area)
    );
}

void OverviewDroneItem::setConnectivity(QString level)
{
    ui->connectivityValue->setText(level);
}

void OverviewDroneItem::updateStatus(DroneStatus status)
{
    lastTimestamp = status.getTimestampReceivedWorkstation();

    double batteryLevel = status.getBatteryLevel();
    if (batteryLevel != -1)
        setBatteryLevel(batteryLevel);
        //ui->batteryValue->setText(QString::number(batteryLevel) + "%");

    if (hasLocation) {
        // calculate the area searched since the last update
        double distance = status.getCurrentLocation().distanceTo(lastLocation);

        searchedArea += distance * visionWidthMeters;
        setSearchedArea(searchedArea);

        // update last location
        lastLocation = status.getCurrentLocation();
    }

    if (!hasLocation) {
        lastLocation = status.getCurrentLocation();
        hasLocation = true;

        // calculate the vision width in meters for this received coordinate
        double newLongitude = lastLocation.longitude() + visionWidthDegrees;
        QGeoCoordinate referenceCoordinate(lastLocation.latitude(), newLongitude);
        visionWidthMeters = referenceCoordinate.distanceTo(lastLocation);
    }

    if (!timer->isActive()) {
        timer->start();
    }

}

int OverviewDroneItem::getPeopleLocated()
{
    return locatedPeople;
}

void OverviewDroneItem::incrementPeopleLocated()
{
    locatedPeople++;
    ui->locatedPeopleValue->setText(QString::number(locatedPeople));
}

void OverviewDroneItem::checkConnectivity()
{
    double delta = QDateTime::currentDateTime().time().msec() - lastTimestamp.time().msec();
    qDebug() << "time " << delta;

    //if (delta < 1.5)


}

