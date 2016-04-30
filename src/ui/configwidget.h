#ifndef CONFIGWIDGET_H
#define CONFIGWIDGET_H

#include <QFile>
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
#include "models/search.h"
#include "core/mediator.h"

namespace Ui {
class ConfigWidget;
}

/*!
 * \brief The ConfigWidget class
 * \ingroup Ui
 */
class ConfigWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ConfigWidget(QWidget *parent = 0);
    ~ConfigWidget();
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void setMediator(Mediator *mediator);

signals:
    void startSearch(Search *s);
    void requestDronesStatus();

public slots:
    void onMapLoaded();
    void onMapFailedToLoad();

private slots:
    void startButtonPush();
    void locateButtonPush();
    void sliderChanged(int);
    void areaSelected(QGeoRectangle area);
    //! \brief slot will listen to incoming DroneStatuses and then update the dronetable
    void updateDroneTable(DroneStatus* s);
    void updateMapCenter(DroneStatus* s);

private:
    Ui::ConfigWidget *ui;
    QMMapView *mapView;
    Mediator *mediator;

    bool areaWasSelected = false;
    bool mapCentered = false;

    double areaOfArea = 0.0;
    constexpr static double MAX_AREA_OF_AREA = 10000.0;
    constexpr static double MIN_AREA_OF_AREA = 1.0;

    void writeConfigToFile();
    void initializeMap();

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
