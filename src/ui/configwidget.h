#ifndef CONFIGWIDGET_H
#define CONFIGWIDGET_H

#include <QWidget>
#include <QStackedWidget>
#include <QKeyEvent>
#include <QLabel>
#include <QMainWindow>
#include <QMMapView.h>
#include <QFile>
#include <QPair>
#include <QList>
#include <QUuid>

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
    //! \brief slot will listen to incoming DroneStatuses and then update the dronetable
    void updateDroneTable();

private:
    Ui::ConfigWidget *ui;
    QMMapView *mapView;
    Controller *controller;

    void initializeMap();

    // connects all the slots and signals with the mediator
    void setSignalSlots();
    // fill the table with the available drones
    // Note: can only be called once a controller is set because only the controller know the drones
    void fillDroneTable();

    QList<QPair<int, Drone*>> dronesInTable;

    enum DroneTableCol {
        CHECK, TYPE, BATTERY, IP_PORT
    };
};

#endif // CONFIGWIDGET_H
