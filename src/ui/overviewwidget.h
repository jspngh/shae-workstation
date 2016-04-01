#ifndef OVERVIEWWIDGET_H
#define OVERVIEWWIDGET_H

#include <QWidget>
#include <QStackedWidget>
#include <QMMapView.h>
#include <QMMapIcon.h>
#include "core/mediator.h"
#include "models/search.h"
#include "communication/dronemodule.h"

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
    Mediator *mediator;

private slots:
    void clickButtonPush();
    void backButtonPush();
    void onSearchStarted(Search *s);
    void onMapLoaded();
    void onMapFailedToLoad();
};

#endif // OVERVIEWWIDGET_H
