/*****************************************************************************
 * QMMapView.h
 *
 * Created: 08/7 2013 by uranusjr
 *
 * Copyright 2013 uranusjr. All rights reserved.
 *
 * This file may be distributed under the terms of GNU Public License version
 * 3 (GPL v3) as defined by the Free Software Foundation (FSF). A copy of the
 * license should have been included with this file, or the project in which
 * this file belongs to. You may also find the details of GPL v3 at:
 * http://www.gnu.org/licenses/gpl-3.0.txt
 *
 * If you have any questions regarding the use of this file, feel free to
 * contact the author of this file, or the owner of the project in which
 * this file belongs to.
 *****************************************************************************/

#ifndef QMMAPVIEW_H
#define QMMAPVIEW_H

#include <QWidget>
#include <QGeoCoordinate>
#include <QGeoRectangle>
#include "QtMapKit.h"

class QMMapViewPrivate;

class QMMapView : public QWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(QMMapView)

public:
    enum MapType {
        Hybrid,
        RoadMap,
        Satellite,
        Terrain
    };

    QMMapView(MapType mapType, QGeoCoordinate center, uint zoomLevel,
              QWidget *parent = 0);

    /*!
     * \brief Returns the display type of the map (e.g. satellite/road, ...)
     */
    MapType mapType() const;

    /*!
     * \brief Returns the region of the map (i.e. the region that is visible on the map)
     *
     * Due to the limitation in the Google Map JavaScript API, this method
     * works only after the first `regionChanged()` signal is sent. The result
     * of any invocation of this method before that is undefined.
     */
    QGeoRectangle region() const;

    /*!
     * \brief Returns the center at the coordinate of the map.
     */
    QGeoCoordinate center() const;

    /*!
     * \brief Returns the zoom level of the map
     */
    uint zoomLevel() const;

    /*!
     * \brief Returns the heading of the map (i.e. the angle of the direction you're taking)
     */
    qreal heading() const;

    /*!
     * \brief Returns the tilt of the map (in degrees). Will be a value in [0,45]
     */
    qreal tilt() const;

    /*!
     * \brief Returns whether an area can be selected on the map.
     */
    bool isSelectable() const;

    /*!
     * \brief Call this when the shift key is pressed
     */
    void shiftKeyPressed(bool down);

public slots:
    /*!
     * \brief Sets the display type of the map (e.g. satellite imagery, roads, ...)
     */
    void setMapType(MapType type);

    /*!
     * \brief Set the center of the map to the given coordinate.
     */
    void setCenter(QGeoCoordinate center, bool animated = true);

    /*!
     * \brief Set the center of the map to the given address.
     * Note: the map will use a best guess for the address' location.
     */
    void setCenter(QString address, bool animated = true);

    /*!
     * \brief Sets the zoom level of the map.
     */
    void setZoomLevel(uint zoom);

    /*!
     * \brief Translates and zooms the map to make the given region visible.
     */
    void makeRegionVisible(QGeoRectangle &region);

    /*!
     * \brief Fits the map area to the given region.
     */
    void fitRegion(QGeoRectangle &region);

    /*!
     * \brief Selects an area from topLeft to bottomRight on the map.
     */
    void selectArea(QGeoRectangle &area);

//    void pan(int x, int y);
//    void setHeading(qreal heading);
//    void setTilt(qreal tile);

protected:
    void resizeEvent(QResizeEvent *);

signals:
    void mapLoaded();
    void mapFailedToLoad();
    void mapBecameIdle();
    void regionChanged(QGeoRectangle region);
    void centerChanged(QGeoCoordinate center);
    void headingChanged();
    void mapTypeChanged(MapType type);
    void tilesLoaded();
    void tilesChanged();
    void zoomLevelChanged(uint level);
    // Mouse signals
    void mouseClicked(QGeoCoordinate coordinate);
    void mouseDoubleClicked(QGeoCoordinate coordinate);
    void mouseRightClicked(QGeoCoordinate coordinate);
    void mouseDragged();
    void mouseDragStarted();
    void mouseDragEnded();
    void cursorMoved(QGeoCoordinate coordinate);
    void cursorEntered(QGeoCoordinate coordinate);
    void cursorLeaved(QGeoCoordinate coordinate);
    // Selected area signals
    void selectedAreaCreated(QGeoRectangle region);
    void selectedAreaChanged(QGeoRectangle region);
    void selectedAreaDeleted();

protected slots:
    void initializeMap();
    void insertNativeObject();
    void regionDidChangeTo(qreal north, qreal south, qreal east, qreal west);
    void centerDidChangeTo(qreal latitude, qreal longitude);
    void mapTypeDidChangeTo(QString typeString);
    // Mouse slots
    void mouseDidClickAt(qreal latitude, qreal longitude);
    void mouseDidDoubleClickAt(qreal latitude, qreal longitude);
    void mouseDidRightClickAt(qreal latitude, qreal longitude);
    void cursorDidMoveTo(qreal latitude, qreal longitude);
    void cursorDidEnterTo(qreal latitude, qreal longitude);
    void cursorDidLeaveFrom(qreal latitude, qreal longitude);
    // Selected area slots
    void selectedAreaWasCreated(qreal topLeftLat, qreal topLeftLong,
                                qreal bottomRightLat, qreal bottomRightLong);
    void selectedAreaDidChangeTo(qreal topLeftLat, qreal topLeftLong,
                                 qreal bottomRightLat, qreal bottomRightLong);
    void selectedAreaWasDeleted();

private:
    bool selectable;
    QMMapViewPrivate *d_ptr;
};

#endif // QMMAPVIEW_H
