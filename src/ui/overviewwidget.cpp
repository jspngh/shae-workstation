#include "overviewwidget.h"
#include "ui_overviewwidget.h"

OverviewWidget::OverviewWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OverviewWidget)
{
    ui->setupUi(this);

    //lowerbuttons:
    connect(ui->clickButton, SIGNAL(clicked()), this, SLOT(clickButtonPush()));
    connect(ui->backButton, SIGNAL(clicked()), this, SLOT(backButtonPush()));
}

OverviewWidget::~OverviewWidget()
{
    delete ui;
}

void OverviewWidget::setMediator(Mediator *mediator)
{
    this->mediator = mediator;
    mediator->addSlot(this, SLOT(onSearchStarted(Search *)), QString("startSearch(Search*)"));
}

void OverviewWidget::clickButtonPush()
{
}

void OverviewWidget::backButtonPush()
{
    ((QStackedWidget *) this->parent())->setCurrentIndex(1);
}

void OverviewWidget::onSearchStarted(Search *s)
{
    mapView = new QMMapView(QMMapView::Satellite,
                            s->getArea().center(),
                            11,
                            true);
    mapView->fitRegion(s->getArea());
    connect(mapView, SIGNAL(mapFailedToLoad()),
            this, SLOT(onMapFailedToLoad()));
    connect(mapView, SIGNAL(mapLoaded()),
            this, SLOT(onMapLoaded()));
}

void OverviewWidget::onMapLoaded()
{
    ui->mainLayout->replaceWidget(ui->mapLoadingLabel, mapView);
    ui->mapLoadingLabel->hide();
}

void OverviewWidget::onMapFailedToLoad()
{
    ui->mapLoadingLabel->setText(QString(
        "Error loading map.\nPlease check your internet connection."
    ));
}

