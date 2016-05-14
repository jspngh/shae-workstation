#ifndef CONFIGWIDGET_H
#define CONFIGWIDGET_H

#include <QCheckBox>
#include <QFile>
#include <QGeoRectangle>
#include <QKeyEvent>
#include <QLabel>
#include <QList>
#include <QMMapView.h>
#include <QMSelectionType.h>
#include <QMainWindow>
#include <QMessageBox>
#include <QPair>
#include <QStackedWidget>
#include <QUuid>
#include <QWidget>
#include <QtMath>
#include <QTimer>
#include "models/search.h"
#include "core/mediator.h"

namespace Ui {
class ConfigWidget;
}

/*!
 * \brief The ConfigWidget class represents the code for the configuration screen.
 * \ingroup Ui
 * The layout is defined in configwidget.ui
 */
class ConfigWidget : public QWidget
{
    Q_OBJECT

public:
    //! constructor
    explicit ConfigWidget(QWidget *parent = 0);
    //! destructor
    ~ConfigWidget();
    //! This is called when a key is pressed
    void keyPressEvent(QKeyEvent *event);
    //! This is called when a key is released
    void keyReleaseEvent(QKeyEvent *event);
    //! Sets the mediator to allow connecting signals and slots without direct dependencies
    void setMediator(Mediator *mediator);

signals:
    //! This signal is emitted when a search is to start, i.e. when the start search buttong is clicked.
    void startSearch(Search *s);
    //! This signal is emitted to ask for the status of the connected drones.
    void requestDronesStatus();

public slots:
    //! When the mapview is loaded, this slot is called. it makes the mapview visible.
    void onMapLoaded();
    //! When the mapview failed to load, this slot is called.
    void onMapFailedToLoad();

private slots:
    //! Called when the start button is pushed, this will check if everything is correct and whill emit startSearch(s)
    void startButtonPush();
    //! Called when the locate button is pushed, this will center the map on the specified location
    void locateButtonPush();
    //! Deprecated: Not used, does not do anything
    void sliderChanged(int);
    void chooseSquare(bool checked);
    void areaDeleted();
    //! \brief slot will listen to incoming DroneStatuses and then update the dronetable
    //! When an area is selected, this slot is called. It will set the boolean areaWasSelected to true.
    void areaSelected();
    //! a slot that will listen to incoming DroneStatuses and then update the dronetable
    void updateDroneTable(DroneStatus* s);
    //! updates the map center
    void updateMapCenter(DroneStatus* s);
    //! this function will reconfigure the configWidget once a user has configured a search and has pressed start
    void onStartSearch(Search *search);
    //! will query all the connected drones for their latest statuses
    void requestStatuses();

private:
    Ui::ConfigWidget *ui;
    QMMapView *mapView = nullptr;
    Mediator *mediator;

    QTimer *timerStatusesRequest;
    QGeoCoordinate center;
    bool areaWasSelected = false;
    bool mapCentered = false;

    double areaOfArea = 0.0;
    constexpr static double MAX_AREA_OF_AREA = 10000.0;
    constexpr static double MIN_AREA_OF_AREA = 1.0;
    constexpr static double MAX_DISTANCE = 500.0;

    void writeConfigToFile();
    void initializeMap();
    //! simple helper function that will initialize some timers used in the configwidget
    //! (e.g. watchdog for querying the dronestatuses)
    void initTimers();
    // connects all the slots and signals with the mediator
    void setSignalSlots();
    // fill the table with the available drones
    // Note: can only be called once a controller is set because only the controller know the drones
    void fillDroneTable();
    int getDroneInTableIndex(DroneModule *d);

    QList<QPair<int, DroneModule *>> dronesInTable;

    enum DroneTableCol {
        CHECK, TYPE, BATTERY, IP_PORT
    };
};

#endif // CONFIGWIDGET_H
