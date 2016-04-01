#ifndef QMMAPICON_H
#define QMMAPICON_H

#include <QObject>
#include <QString>
#include <QPair>

/*!
 * \note (0,0) is topleft of the icon.
 */
class QMMapIcon : public QObject
{
    Q_OBJECT

private:
    QString resource;
    QPair<int, int> size;
    QPair<int, int> origin;
    QPair<int, int> anchor;

public:
    QMMapIcon(QString resource, QObject *parent = 0);
    ~QMMapIcon();

    void setSize(int width, int height);
    void setOrigin(int x, int y);
    void setAnchor(int x, int y);

    QString toJsObject();
};

#endif // QMMAPICON_H

