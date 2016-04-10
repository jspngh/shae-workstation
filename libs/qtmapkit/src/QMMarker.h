#ifndef QMMARKER_H
#define QMMARKER_H

#include <QGeoCoordinate>
#include <QObject>
#include <QString>
#include <QVariant>
#include <QWebFrame>

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

    double orientation() const;

public slots:
    /*!
     * Shows the icon on the map.
     */
    void show();

    /*!
     * Moves the icon to the given location.
     * \param to The location to move the marker to.
     */
    void moveTo(const QGeoCoordinate &to);

    /*!
     * Rotates the marker.
     * \param degrees The amount of degrees the the marker should be rotated.
     */
    void rotate(const double degrees);

    /*!
     * Sets the orientation of the marker. This also means any previous rotations
     * will be undone.
     * \param degrees The amount of degrees the the marker should be rotated.
     */
    void setOrientation(const double degrees);

    /*!
     * Scales the marker by a given amount.
     * \param width The scale of the new width.
     * \param height The scale of the new height.
     */
    void scale(const double width, const double height);

    /*!
     * Sets the markers icon.
     * \param resource The resource url to the image file.
     */
    void setIcon(const QString resource);

private:
    QMMarkerPrivate *d_ptr;
};

#endif // QMMARKER_H

