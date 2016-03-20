#ifndef CONFIGWIDGET_H
#define CONFIGWIDGET_H

#include <QWidget>
#include <QStackedWidget>
#include <QKeyEvent>
#include <QLabel>
#include <QMainWindow>
#include <QMMapView.h>
#include <QFile>
#include "core/mediator.h"

namespace Ui {
class ConfigWidget;
}

class ConfigWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ConfigWidget(QWidget *parent = 0);
    ~ConfigWidget();
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void setMediator(Mediator *mediator);

private:
    Ui::ConfigWidget *ui;
    Mediator *mediator;
    QMMapView *mapView;
    void initializeMap();

public slots:
    void onMapLoaded();
    void onMapFailedToLoad();
    void initConfScreen(QString);

private slots:
    void startButtonPush();
    void backButtonPush();
    void locateButtonPush();
    void sliderChanged(int);
};

#endif // CONFIGWIDGET_H
