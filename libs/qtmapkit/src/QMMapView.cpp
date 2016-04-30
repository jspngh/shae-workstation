/*****************************************************************************
 * QMMapView.cpp
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

#include "QMMapView.h"
#include <QHBoxLayout>
#include <QHash>
#include <QMap>
#include <QString>
#include <QtDebug>
#include <QVariantMap>
#include <QWebFrame>
#include <QWebView>

class CustomWebPage : public QWebPage
{
public:
    CustomWebPage(QObject *parent = 0) : QWebPage(parent) {}

protected:
    void javaScriptConsoleMessage(const QString &message, int lineNumber,
                                  const QString &sourceID)
    {
        qDebug() << "JavaScript" << sourceID << "line" << lineNumber <<
                 ":" << message;
    }
};

class QMMapViewPrivate
{
    Q_DECLARE_PUBLIC(QMMapView)

public:
    QMMapViewPrivate(QMMapView *q) : q_ptr(q), loaded(false)
    {
        // Only necessary when building as a static library
        Q_INIT_RESOURCE(qtmapkit_resources);
        webView = new QWebView();
        webView->setPage(new CustomWebPage());
        webView->load(QUrl("qrc:///qtmapkit/gmap/gmap.html"));
    }
    ~QMMapViewPrivate() {}
    QMMapView *q_ptr;

    bool loaded;
    QWebView *webView;
    struct {
        QGeoCoordinate centerCoordinate;
        QMMapView::MapType mapType;
        uint zoomLevel;
    } initialValues;
    QMSelectionType selectionType;
    QMap<QString, QMMarker *> markers;

    inline QWebFrame *frame() { return webView->page()->mainFrame(); }
    inline QVariant evaluateJavaScript(const QString &script,
                                       bool force = false)
    {
        if (loaded || force)
            return frame()->evaluateJavaScript(script);
        else
            return QVariant();
    }
    inline QString toJsMapType(QMMapView::MapType type)
    {
        QString typeName;
        switch (type) {
        case QMMapView::Hybrid:
            typeName = "HYBRID";
            break;
        case QMMapView::RoadMap:
            typeName = "ROADMAP";
            break;
        case QMMapView::Satellite:
            typeName = "SATELLITE";
            break;
        case QMMapView::Terrain:
            typeName = "TERRAIN";
            break;
        default:
            break;
        }
        return QString("google.maps.MapTypeId.%1").arg(typeName);
    }
    inline QMMapView::MapType fromJsMapType(QString &type)
    {
        static QHash<QString, QMMapView::MapType> types;
        if (types.isEmpty()) {
            types.insert("hybrid", QMMapView::Hybrid);
            types.insert("roadmap", QMMapView::RoadMap);
            types.insert("satellite", QMMapView::Satellite);
            types.insert("terrain", QMMapView::Terrain);
        }
        return types.value(type, initialValues.mapType);
    }
};

QMMapView::QMMapView(MapType mapType, QGeoCoordinate center, uint zoomLevel,
                     QWidget *parent) :
    QWidget(parent), d_ptr(new QMMapViewPrivate(this))
{
    Q_D(QMMapView);

    QHBoxLayout *mainLayout = new QHBoxLayout();
    mainLayout->addWidget(d->webView);
    setLayout(mainLayout);

    d->initialValues.centerCoordinate = center;
    d->initialValues.mapType = mapType;
    d->initialValues.zoomLevel = zoomLevel;
    d->selectionType = QMSelectionType::None;
    connect(d->frame(), SIGNAL(javaScriptWindowObjectCleared()),
            this, SLOT(insertNativeObject()));
    connect(d->webView, SIGNAL(loadFinished(bool)),
            this, SLOT(initializeMap()));
}

void QMMapView::insertNativeObject()
{
    Q_D(QMMapView);
    d->frame()->addToJavaScriptWindowObject("qMapView", this);
}

void QMMapView::initializeMap()
{
    Q_D(QMMapView);
    QGeoCoordinate &center = d->initialValues.centerCoordinate;
    QString js = QString("initialize(%1, %2, %3, %4);")
                 .arg(center.longitude()).arg(center.latitude())
                 .arg(d->toJsMapType(d->initialValues.mapType))
                 .arg(QString::number(d->initialValues.zoomLevel));
    bool success = d->evaluateJavaScript(js, true).toBool();

    if (success) {
        d->loaded = true;
        emit mapLoaded();
    } else {
        emit mapFailedToLoad();
    }
}

void QMMapView::resizeEvent(QResizeEvent *)
{
    Q_D(QMMapView);
    d->evaluateJavaScript("google.maps.event.trigger(mapKit.map, 'resize');");
}

bool QMMapView::hasLoaded() const
{
    Q_D(const QMMapView);
    return d->loaded;
}

QMMapView::MapType QMMapView::mapType() const
{
    QString res = d_ptr->evaluateJavaScript("mapKit.map.getMapTypeId();").toString();
    return d_ptr->fromJsMapType(res);
}

QGeoRectangle QMMapView::region() const
{
    QVariant result = d_ptr->evaluateJavaScript("mapKit.getMapBounds();");
    return jsonObjectToQGeoRectangle(result);
}

QGeoCoordinate QMMapView::center() const
{
    QVariantMap result = d_ptr->evaluateJavaScript("mapKit.getCenter();").toMap();
    return QGeoCoordinate(result["latitude"].toReal(),
                          result["longitude"].toReal());
}

uint QMMapView::zoomLevel() const
{
    return d_ptr->evaluateJavaScript("mapKit.map.getZoom();").toUInt();
}

qreal QMMapView::heading() const
{
    return d_ptr->evaluateJavaScript("mapKit.map.getHeading();").toReal();
}

qreal QMMapView::tilt() const
{
    return d_ptr->evaluateJavaScript("mapKit.map.getTilt();").toReal();
}

QGeoShape QMMapView::selectedArea() const
{
    QString script = QString("mapKit.mapSelection.getSelectedArea();");
    QVariant result = d_ptr->evaluateJavaScript(script);
    if(selectionType() == QMSelectionType::Square) {
        return jsonObjectToQGeoRectangle(result);
    } else {
        if(selectionType() == QMSelectionType::Polygon) {
            return jsonObjectToQGeoRectangle(result);
        } else {
            throw new EmptyAreaException();
        }
    }
}

QGeoRectangle QMMapView::jsonObjectToQGeoRectangle(const QVariant jsObject) const
{
    if (jsObject.isNull() || !jsObject.isValid())
        throw new EmptyAreaException();

    QVariantMap objectMap = jsObject.toMap();
    if (!(objectMap.contains("north") && objectMap.contains("south")
            && objectMap.contains("east") && objectMap.contains("west")))
        throw new EmptyAreaException();

    return QGeoRectangle(QGeoCoordinate(objectMap.value("north").toReal(),
                                        objectMap.value("west").toReal()),
                         QGeoCoordinate(objectMap.value("south").toReal(),
                                        objectMap.value("east").toReal()));
}

void QMMapView::setMapType(const MapType type)
{
    Q_D(QMMapView);
    QString typeName = d->toJsMapType(type);
    QString script = QString("mapKit.map.setMapTypeId(%1);").arg(typeName);
    d->evaluateJavaScript(script);
}

void QMMapView::setCenter(const QGeoCoordinate center, bool animated)
{
    Q_D(QMMapView);
    QString format = QString("mapKit.setCenter(%1, %2, %3);");
    QString js = format
                 .arg(center.latitude()).arg(center.longitude())
                 .arg(animated ? "true" : "false");
    d->evaluateJavaScript(js);
}

void QMMapView::setCenter(const QString address, const bool animated)
{
    Q_D(QMMapView);
    QString format = QString("mapKit.setCenterByAddress(\"%1\", %2);");
    QString js = format.arg(address).arg(animated);
    d->evaluateJavaScript(js);
}

void QMMapView::setZoomLevel(const uint zoom)
{
    Q_D(QMMapView);
    d->evaluateJavaScript(QString("mapKit.map.setZoom(%1);").arg(zoom));
}

void QMMapView::makeRegionVisible(const QGeoRectangle &region)
{
    Q_D(QMMapView);
    QString format = QString("mapKit.panToBounds(%1, %2, %3, %4);");
    QString js = format
                 .arg(region.topLeft().latitude()).arg(region.bottomLeft().latitude())
                 .arg(region.topRight().longitude()).arg(region.topLeft().longitude());
    d->evaluateJavaScript(js);
}

void QMMapView::fitRegion(const QGeoRectangle &region)
{
    Q_D(QMMapView);
    QString format = QString("mapKit.fitBounds(%1, %2, %3, %4);");
    QString js = format
                 .arg(region.topLeft().latitude()).arg(region.bottomLeft().latitude())
                 .arg(region.topRight().longitude()).arg(region.topLeft().longitude());
    d->evaluateJavaScript(js);
}

bool QMMapView::selectable() const
{
    Q_D(const QMMapView);
    return d->selectionType == QMSelectionType::None;
}

QMSelectionType QMMapView::selectionType() const
{
    Q_D(const QMMapView);
    return d->selectionType;
}

void QMMapView::setSelectionType(const QMSelectionType selectionType)
{
    Q_D(QMMapView);
    QString format = QString("mapKit.setSelectable(\"%1\");");

    QString typeName;
    switch(selectionType) {
        case QMSelectionType::Polygon:
            typeName = "polygon";
            break;
        case QMSelectionType::Square:
            typeName = "square";
            break;
        default:
            typeName = "";
            break;
    }

    QString js = format.arg(typeName);
    d->evaluateJavaScript(js);
}

void QMMapView::shiftKeyPressed(bool down)
{
    Q_D(QMMapView);

    if (!selectable())
        return;

    if (down) {
        d->evaluateJavaScript("mapKit.shiftKeyDown();");
    } else {
        d->evaluateJavaScript("mapKit.shiftKeyUp();");
    }
}

void QMMapView::selectArea(const QGeoRectangle &area)
{
    Q_D(QMMapView);
    QString format = QString("mapKit.selectAreaOnMap(%1, %2, %3, %4);");
    QString js = format
                 .arg(area.topLeft().latitude()).arg(area.topLeft().latitude())
                 .arg(area.bottomRight().longitude()).arg(area.bottomRight().longitude());
    d->evaluateJavaScript(js);
}

/* void QMMapView::selectArea(const QGeoRectangle &area) */
/* { */
/*     Q_D(QMMapView); */
/*     QString format = QString("mapKit.selectAreaOnMap(%1, %2, %3, %4);"); */
/*     QString js = format */
/*                  .arg(area.topLeft().latitude()).arg(area.topLeft().latitude()) */
/*                  .arg(area.bottomRight().longitude()).arg(area.bottomRight().longitude()); */
/*     d->evaluateJavaScript(js); */
/* } */

QMMarker &QMMapView::addMarker(const QString markerId, const QGeoCoordinate &point)
{
    Q_D(QMMapView);
    QString format = QString("mapKit.addMarker(\"%1\", %2, %3);");
    QString js = format
                 .arg(markerId)
                 .arg(point.latitude(),0,'f',15).arg(point.longitude(),0,'f',15);
    d->evaluateJavaScript(js);
    d->markers[markerId] = new QMMarker(markerId, point, d->frame(), this);

    return getMarker(markerId);
}

QMMarker &QMMapView::getMarker(const QString markerId)
{
    Q_D(QMMapView);
    return *(d->markers.value(markerId));
}

bool QMMapView::hasMarker(const QString markerId) const
{
    Q_D(const QMMapView);
    return d->markers.contains(markerId);
}

void QMMapView::removeMarker(const QString markerId)
{
    Q_D(QMMapView);
    QString js = QString("mapKit.removeMarker(\"%1\");").arg(markerId);
    d->evaluateJavaScript(js);
    QMMarker *removedMarker = d->markers.take(markerId);
    delete removedMarker;
}

void QMMapView::jsRegionChangedTo(qreal north, qreal south,
                                  qreal east, qreal west)
{
    emit regionChanged(
        QGeoRectangle(
            QGeoCoordinate(north, west),
            QGeoCoordinate(south, east)
        ));
}

void QMMapView::jsCenterChangedTo(qreal latitude, qreal longitude)
{
    emit centerChanged(QGeoCoordinate(latitude, longitude));
}

void QMMapView::jsMapTypeChangedTo(QString typeString)
{
    Q_D(QMMapView);
    emit mapTypeChanged(d->fromJsMapType(typeString));
}

void QMMapView::jsMouseClickedAt(qreal latitude, qreal longitude)
{
    emit mouseClicked(QGeoCoordinate(latitude, longitude));
}

void QMMapView::jsMouseDoubleClickedAt(qreal latitude, qreal longitude)
{
    emit mouseDoubleClicked(QGeoCoordinate(latitude, longitude));
}

void QMMapView::jsMouseRightClickedAt(qreal latitude, qreal longitude)
{
    emit mouseRightClicked(QGeoCoordinate(latitude, longitude));
}

void QMMapView::jsMouseMovedTo(qreal latitude, qreal longitude)
{
    emit cursorMoved(QGeoCoordinate(latitude, longitude));
}

void QMMapView::jsMouseEnteredAt(qreal latitude, qreal longitude)
{
    emit cursorEntered(QGeoCoordinate(latitude, longitude));
}

void QMMapView::jsMouseLeftAt(qreal latitude, qreal longitude)
{
    emit cursorLeaved(QGeoCoordinate(latitude, longitude));
}

void QMMapView::jsSelectedAreaCreated(qreal topLeftLat, qreal topLeftLong,
                                      qreal bottomRightLat, qreal bottomRightLong)
{
    QGeoRectangle selectedArea = QGeoRectangle(
                                     QGeoCoordinate(topLeftLat, topLeftLong),
                                     QGeoCoordinate(bottomRightLat, bottomRightLong)
                                 );
    emit selectedAreaCreated(selectedArea);
}

void QMMapView::jsSelectedAreaChanged(qreal topLeftLat, qreal topLeftLong,
                                      qreal bottomRightLat, qreal bottomRightLong)
{
    QGeoRectangle selectedArea = QGeoRectangle(
                                     QGeoCoordinate(topLeftLat, topLeftLong),
                                     QGeoCoordinate(bottomRightLat, bottomRightLong)
                                 );
    emit selectedAreaChanged(selectedArea);
}

void QMMapView::jsSelectedAreaDeleted()
{
    emit selectedAreaDeleted();
}

