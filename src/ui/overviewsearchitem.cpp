#include "overviewsearchitem.h"
#include "ui_overviewsearchitem.h"

OverviewSearchItem::OverviewSearchItem(Search *search, QWidget *parent)
    : QWidget(parent),
      ui(new Ui::OverviewSearchItem)
{
    ui->setupUi(this);
}

OverviewSearchItem::~OverviewSearchItem()
{
    delete ui;
}

void OverviewSearchItem::setLocatedPeople(int nrPeople)
{
    ui->locatedPeopleValue->setText(QString::number(nrPeople));
}

void OverviewSearchItem::setDuration(int seconds)
{
    QString format = QString("%1:%2");
    QString time = format.arg(seconds / 60, 2, 10, QChar('0'))
                         .arg(seconds % 60, 2, 10, QChar('0'));
    ui->durationValue->setText(time);
}

void OverviewSearchItem::setSearchedArea(double area)
{
    ui->searchAreaValue->setText(QString::number(area) + "m²");
}

