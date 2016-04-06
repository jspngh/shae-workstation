#ifndef QMMARKER_H
#define QMMARKER_H

#include <QGeoCoordinate>
#include <QObject>
#include <QString>
#include <QVariant>
#include <QWebFrame>
#include "QMMapIcon.h"

class QMMarkerPrivate;

/*!
 * A QMMarker represents a marker on the map.
 */
class QMMarker : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(QMMarker)

public:
    /*!
     * Creates a QMMarker with the given QWebFrame, in which all javascript
     * will be executed.
     * \param object The identifier or method that needs to be called in the
     *           javascript-context to retrieve the marker.
     * \param frame The frame in which the javascript will be executed.
     */
    QMMarker(QString object, const QGeoCoordinate &location, QWebFrame *frame, QObject *parent = 0);

    QGeoCoordinate location() const;
    /* QMMapIcon icon() const; */

public slots:
    void show();
    void moveTo(const QGeoCoordinate &to);
    void rotate(const int degrees);
    void setIcon(const QMMapIcon &icon);

private:
    QMMarkerPrivate *d_ptr;
};

#endif // QMMARKER_H

