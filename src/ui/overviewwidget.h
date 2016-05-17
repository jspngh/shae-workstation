#ifndef OVERVIEWWIDGET_H
#define OVERVIEWWIDGET_H

#include <QListWidgetItem>
#include <QMap>
#include <QtMath>
#include <QMMarker.h>
#include <QMMapView.h>
#include <QUuid>
#include <QWidget>
#include "overviewdroneitem.h"
#include "overviewsearchitem.h"
#include "communication/dronemodule.h"
#include "core/mediator.h"
#include "models/detectionresult.h"
#include "models/search.h"
#include "ui/summarydialog.h"

namespace Ui {
class OverviewWidget;
}
/*!
 * \brief The OverviewWidget class represents the code for the overview screen.
 * \ingroup Ui
 * The layout is defined in overviewwidget.ui
 */
class OverviewWidget : public QWidget
{
    Q_OBJECT

public:
    //! Constructor
    explicit OverviewWidget(QWidget *parent = 0);
    //! Destructor
    ~OverviewWidget();
    //! Sets mediator
    void setMediator(Mediator *mediator);
    //! gets summarydialog
    SummaryDialog *getSummaryDialog() const;

private:
    //! pointer to layout
    Ui::OverviewWidget *ui;
    //! pointer to the mapview
    QMMapView *mapView;
    //! bool to check if mapview loaded
    bool mapViewLoaded;
    //! the search details
    OverviewSearchItem *searchDetails;
    //! the summary dialog displays option to save footage, save the search results, or just close the app
    SummaryDialog *summaryDialog;
    //! pointer to the current Search object
    Search *search;
    //! pointer to the mediator
    Mediator *mediator;
    //! table with overviewItems
    QMap<QUuid, OverviewDroneItem *> mapIdListItem;

private slots:
    //! slot for when a drone is landed
    void onDroneLanded(DroneModule *drone);
    //! slot for when a search is started
    void onSearchStarted(Search *s);
    //! Slot for when a heartbeat is received
    void onHeartBeatReceived(DroneStatus *heartbeat);
    //! slot for when a human is detected
    void onNewDetection(QUuid droneId, DetectionResult* result);
    //! slot to fill the list of connected drones
    void fillDroneList();
    //! slot to update the droneList with a new status
    void updateDroneList(DroneStatus *s);
    //! slot for when the mapview is loaded
    void onMapLoaded();
    //! slot for when the mapview failed to load
    void onMapFailedToLoad();
};

#endif // OVERVIEWWIDGET_H
