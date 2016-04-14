#ifndef OVERVIEWSEARCHITEM_H
#define OVERVIEWSEARCHITEM_H

#include <QChar>
#include <QString>
#include <QTimer>
#include <QWidget>
#include "models/search.h"

namespace Ui {
class OverviewSearchItem;
}

class OverviewSearchItem : public QWidget
{
    Q_OBJECT

public:
    explicit OverviewSearchItem(Search *search, QWidget *parent = 0);
    ~OverviewSearchItem();

public slots:
    void setLocatedPeople(int nrPeople);
    void setSearchedArea(double area);

private slots:
    void incrementDuration();

private:
    Ui::OverviewSearchItem *ui;
    QTimer *timer;
    int duration;
};

#endif // OVERVIEWSEARCHITEM_H

