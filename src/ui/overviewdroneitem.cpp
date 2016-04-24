#include "overviewdroneitem.h"
#include "ui_overviewdroneitem.h"

OverviewDroneItem::OverviewDroneItem(DroneModule *drone, uint number, QWidget *parent)
    : QWidget(parent),
      ui(new Ui::OverviewDroneItem),
      locatedPeople(0),
      searchedArea(0.0),
      receivedStatus(false),
      visionWidthMeters(0.0),
      visionWidthDegrees(drone->getVisionWidth()),
      timer(new QTimer())
{
    ui->setupUi(this);

    setDroneNr(number);

    // init timer
    timer->setInterval(1000);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateConnectivity()));
    timer->start();

    connect(ui->emergencyButton, SIGNAL(clicked()), drone, SLOT(emergencyLanding()));
    connect(ui->haltButton, SIGNAL(clicked()), drone, SLOT(stopFlight()));
    connect(ui->returnHomeButton, SIGNAL(clicked()), drone, SLOT(returnToHome()));
}

OverviewDroneItem::~OverviewDroneItem()
{
    delete ui;
}

void OverviewDroneItem::setStatus(QString status)
{
    ui->statusValue->setText(status);
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
        QString("%1 m²").arg( (int) area)
    );
}

void OverviewDroneItem::setConnectivity(QString level)
{
    ui->connectivityValue->setText(level);
}

void OverviewDroneItem::updateStatus(DroneStatus status)
{
    double batteryLevel = status.getBatteryLevel();
    if (batteryLevel != -1)
        setBatteryLevel(batteryLevel);

    if (receivedStatus) {
        updateSearchedArea(status);
    }

    // update last status
    lastStatus = status;

    // do some initialization work only when the first heartbeat arrives
    if (!receivedStatus) {
        receivedStatus = true;
        calculateVisionWidthMeters();
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

void OverviewDroneItem::updateConnectivity()
{
    if (receivedStatus) {
        QDateTime lastTimestamp = lastStatus.getTimestampReceivedWorkstation();
        double delta = (lastTimestamp.time().msecsTo(QDateTime::currentDateTime().time())) / 1000.0;

        if (delta < 2.0)
            setConnectivity("good");
        else if (delta < 5.0)
            setConnectivity("poor");
        else if (delta < 20.0)
            setConnectivity("bad");
        else
            setConnectivity("no signal");
    }
}

/******************************
 *   Private Helper Functions *
 * ****************************/

void OverviewDroneItem::updateSearchedArea(DroneStatus status)
{
    QGeoCoordinate lastLocation = lastStatus.getCurrentLocation();
    double distance = status.getCurrentLocation().distanceTo(lastLocation);
    searchedArea += (distance * visionWidthMeters);
    setSearchedArea(searchedArea);
}

void OverviewDroneItem::calculateVisionWidthMeters()
{
    QGeoCoordinate lastLocation = lastStatus.getCurrentLocation();
    double newLongitude = lastLocation.longitude() + visionWidthDegrees;
    QGeoCoordinate referenceCoordinate(lastLocation.latitude(), newLongitude);
    visionWidthMeters = referenceCoordinate.distanceTo(lastLocation);
}
