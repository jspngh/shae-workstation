#ifndef CONFIGWIDGET_H
#define CONFIGWIDGET_H

#include <QWidget>
#include <QStackedWidget>
#include <QKeyEvent>
#include <QLabel>
#include <QMainWindow>
#include <QMMapView.h>
#include <QFile>

#include "models/search.h"

class Controller;

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
    void setController(Controller *value);

signals:
    void startSearch(Search *s);

public slots:
    void onMapLoaded();
    void onMapFailedToLoad();
    void initConfScreen(QString);

private slots:
    void startButtonPush();
    void backButtonPush();
    void locateButtonPush();
    void sliderChanged(int);

private:
    Ui::ConfigWidget *ui;
    QMMapView *mapView;
    Controller *controller;


    void writeConfigToFile();
    void initializeMap();
};

#endif // CONFIGWIDGET_H
