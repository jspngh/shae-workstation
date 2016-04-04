#ifndef OVERVIEWWIDGET_H
#define OVERVIEWWIDGET_H

#include <QWidget>
#include <QStackedWidget>
#include <QMMapView.h>
#include <QMMapIcon.h>
#include "overviewdroneitem.h"
#include "communication/dronemodule.h"
#include "core/mediator.h"
#include "models/search.h"

namespace Ui {
class OverviewWidget;
}

class OverviewWidget : public QWidget
{
    Q_OBJECT

public:
    explicit OverviewWidget(QWidget *parent = 0);
    ~OverviewWidget();
    void setMediator(Mediator *mediator);

private:
    QMMapView *mapView;
    Ui::OverviewWidget *ui;
    Search *search;
    Mediator *mediator;

private slots:
    void clickButtonPush();
    void backButtonPush();
    void onSearchStarted(Search *s);
    void fillDroneList();
    void onMapLoaded();
    void onMapFailedToLoad();
};

#endif // OVERVIEWWIDGET_H
