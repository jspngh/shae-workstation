#ifndef QTMAPKIT_TEST_H
#define QTMAPKIT_TEST_H

#include <QString>
#include <QWidget>
#include <QtTest/QtTest>
#include <QMMapView.h>
#include "ui/configwidget.h"

class QtMapKit_Test : public QObject
{
    Q_OBJECT

private:

public:
    QtMapKit_Test();
    ~QtMapKit_Test();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();

    void testMapViewInitialized();
};

#endif // QTMAPKIT_TEST_H

