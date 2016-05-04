#include "overviewsearchitem.h"
#include "ui_overviewsearchitem.h"

OverviewSearchItem::OverviewSearchItem(Search *search, QWidget *parent)
    : QWidget(parent),
      ui(new Ui::OverviewSearchItem),
      timer(new QTimer(this)),
      duration(0),
      locatedPeople(0)
{
    ui->setupUi(this);

    timer->setInterval(1000);
    connect(timer, SIGNAL(timeout()), this, SLOT(incrementDuration()));
    timer->start();
}

OverviewSearchItem::~OverviewSearchItem()
{
    delete ui;
}

void OverviewSearchItem::incrementPeopleLocated()
{
    locatedPeople++;
    ui->locatedPeopleValue->setText(QString::number(locatedPeople));
}

void OverviewSearchItem::incrementDuration()
{
    duration++;
    QString format = QString("%1:%2");
    QString time = format.arg(duration / 60, 2, 10, QChar('0'))
                   .arg(duration % 60, 2, 10, QChar('0'));
    ui->durationValue->setText(time);
}

