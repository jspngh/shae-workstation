#ifndef OVERVIEWSEARCHITEM_H
#define OVERVIEWSEARCHITEM_H

#include <QChar>
#include <QString>
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
    void setDuration(int seconds);
    void setSearchedArea(double area);

private:
    Ui::OverviewSearchItem *ui;
};

#endif // OVERVIEWSEARCHITEM_H

