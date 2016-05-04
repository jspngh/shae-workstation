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
#include <QGeoShape>
#include <QGeoRectangle>
#include "EmptyAreaException.h"
#include "GeoPolygon.h"
#include "QMMarker.h"
#include "QMSelectionType.h"
#include "QtMapKit.h"

class QMMapViewPrivate;

/*!
 * \brief QMMapView provides a Google Maps-widget. It also providess extra
 *        features, such as area selection.
 * \warning Do not use the protected slots prefixed with "js" for your C++
 *          code, as these are used internally and would result in an infinite
 *          loop.
 */
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
     * Returns whether the map has loaded and is safe to perform functions on.
     */
    bool hasLoaded() const;

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
     * \brief Returns the selected area on the map.
     * \throws EmptyAreaException if there was no area selected.
     * \returns The selected area on the map, or null if there is none.
     */
    QGeoShape* selectedArea() const;

    /*!
     * \brief Returns what kind of area can be selected on the map.
     */
    QMSelectionType selectionType() const;

    /*!
     * \brief Returns whether an area can be selected on the map.
     */
    bool selectable() const;

    /*!
     * \brief Call this when the shift key is pressed
     */
    void shiftKeyPressed(bool down);

private:
    QGeoRectangle* jsonObjectToQGeoRectangle(const QVariant jsObject) const;
    GeoPolygon* jsonObjectToGeoPolygon(const QVariant jsObject) const;

public slots:
    /*!
     * \brief Sets the display type of the map (e.g. satellite imagery, roads, ...)
     */
    void setMapType(const MapType type);

    /*!
     * \brief Set the center of the map to the given coordinate.
     */
    void setCenter(const QGeoCoordinate center, const bool animated = true);

    /*!
     * \brief Set the center of the map to the given address.
     * Note: the map will use a best guess for the address' location.
     */
    void setCenter(const QString address, const bool animated = true);

    /*!
     * \brief Sets the zoom level of the map.
     */
    void setZoomLevel(const uint zoom);

    /*!
     * \brief Translates and zooms the map to make the given region visible.
     */
    void makeRegionVisible(const QGeoRectangle &region);

    /*!
     * \brief Fits the map area to the given region.
     */
    void fitRegion(const QGeoRectangle &region);

    /*!
     * \brief Sets the type of area that can be selected on the map.
     */
    void setSelectionType(const QMSelectionType selectionType);

    /*!
     * \brief Selects an area from topLeft to bottomRight on the map.
     */
    void selectArea(QGeoShape *area);

    /*!
     * \brief Removes all selected areas from the map.
     */
    void removeAllSelections();

    /*!
     * \brief Adds a marker on a given location.
     * \param markerId The id of the maerker
     * \param location The coordinate of the marker
     */
    QMMarker &addMarker(QString markerId, const QGeoCoordinate &location);

    /*!
     * \brief Checks whether a marker with the given id exists.
     * \param markerId The id of the maerker
     */
    bool hasMarker(const QString markerId) const;

    /*!
     * \brief Get a marker.
     * \param markerId The id of the maerker
     */
    QMMarker &getMarker(const QString markerId);

    /*!
     * \brief Removes a marker.
     * \param markerId The id of the maerker
     */
    void removeMarker(const QString markerId);

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
    void selectedAreaCreated(QGeoShape region);
    void selectedAreaChanged(QGeoShape region);
    void selectedAreaDeleted();

protected slots:
    void initializeMap();
    void insertNativeObject();
    void jsRegionChangedTo(qreal north, qreal south, qreal east, qreal west);
    void jsCenterChangedTo(qreal latitude, qreal longitude);
    void jsMapTypeChangedTo(QString typeString);
    void jsMouseClickedAt(qreal latitude, qreal longitude);
    void jsMouseDoubleClickedAt(qreal latitude, qreal longitude);
    void jsMouseRightClickedAt(qreal latitude, qreal longitude);
    void jsMouseMovedTo(qreal latitude, qreal longitude);
    void jsMouseEnteredAt(qreal latitude, qreal longitude);
    void jsMouseLeftAt(qreal latitude, qreal longitude);
    void jsSelectedAreaCreated(qreal topLeftLat, qreal topLeftLong,
                               qreal bottomRightLat, qreal bottomRightLong);
    void jsSelectedAreaChanged(qreal topLeftLat, qreal topLeftLong,
                               qreal bottomRightLat, qreal bottomRightLong);
    void jsSelectedAreaDeleted();

private:
    QMMapViewPrivate *d_ptr;
};

#endif // QMMAPVIEW_H
