QT       += webkit
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets webkitwidgets

TARGET = qtmapkit
TEMPLATE = lib
CONFIG += staticlib

DEFINES += QTMAPKIT_LIBRARY

DESTDIR = $$PWD/../lib
OBJECTS_DIR = $$PWD/../build
MOC_DIR = $$PWD/../build
RCC_DIR = $$PWD/../build
UI_DIR = $$PWD/../build

SOURCES += \
    $$PWD/QMMapView.cpp \
    $$PWD/QMCoordinate.cpp \
    $$PWD/QMCoordinateRegion.cpp \
    $$PWD/QMCoordinateSpan.cpp

HEADERS += \
    $$PWD/QtMapKit.h \
    $$PWD/qtmapkit_global.h \
    $$PWD/QMMapView.h \
    $$PWD/QMCoordinate.h \
    $$PWD/QMCoordinateRegion.h \
    $$PWD/QMCoordinateSpan.h

RESOURCES += \
    $$PWD/qtmapkit_resources.qrc

OTHER_FILES += \
    $$PWD/gmap.html \
    $$PWD/gmap.js

# Send headers to include-folder
QMAKE_EXTRA_TARGETS += public_headers
POST_TARGETDEPS += public_headers
public_headers.commands += "mkdir -p $$PWD/../include;"
public_headers.commands += "cp $$HEADERS $$PWD/../include;"

