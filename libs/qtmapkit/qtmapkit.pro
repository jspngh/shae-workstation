QT       += webkit
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets webkitwidgets

TARGET = qtmapkit
TEMPLATE = lib
CONFIG += staticlib

DEFINES += QTMAPKIT_LIBRARY

ROOTDIR = $$PWD/../../
DESTDIR = $$ROOTDIR/bin/lib/
OBJECTS_DIR = $$ROOTDIR/build/lib/
MOC_DIR = $$ROOTDIR/build/lib/
RCC_DIR = $$ROOTDIR/build/lib/
UI_DIR = $$ROOTDIR/build/lib/

SOURCES += \
    $$PWD/src/QMMapView.cpp \
    $$PWD/src/QMCoordinate.cpp \
    $$PWD/src/QMCoordinateRegion.cpp \
    $$PWD/src/QMCoordinateSpan.cpp

HEADERS += \
    $$PWD/src/QtMapKit.h \
    $$PWD/src/qtmapkit_global.h \
    $$PWD/src/QMMapView.h \
    $$PWD/src/QMCoordinate.h \
    $$PWD/src/QMCoordinateRegion.h \
    $$PWD/src/QMCoordinateSpan.h

RESOURCES += \
    $$PWD/src/qtmapkit_resources.qrc

OTHER_FILES += \
    $$PWD/src/gmap.html \
    $$PWD/src/gmap.js

# Send headers to include-folder
QMAKE_EXTRA_TARGETS += public_headers
POST_TARGETDEPS += public_headers
public_headers.commands += "mkdir -p $$ROOTDIR/build/include;"
public_headers.commands += "cp $$HEADERS $$ROOTDIR/build/include;"

