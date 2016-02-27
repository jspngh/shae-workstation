QT       += webkit positioning
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets webkitwidgets

TARGET = qtmapkit
TEMPLATE = lib
CONFIG += staticlib

DEFINES += QTMAPKIT_LIBRARY

DESTDIR = $$PWD/bin
OBJECTS_DIR = $$PWD/build/
MOC_DIR = $$PWD/build/
RCC_DIR = $$PWD/build/
UI_DIR = $$PWD/build/

SOURCES += \
    $$PWD/src/QMMapView.cpp \
    $$PWD/src/QMCoordinateRegion.cpp \
    $$PWD/src/QMCoordinateSpan.cpp

HEADERS += \
    $$PWD/src/QtMapKit.h \
    $$PWD/src/qtmapkit_global.h \
    $$PWD/src/QMMapView.h \
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
public_headers.commands += "mkdir -p $$PWD/include;"
public_headers.commands += "cp $$HEADERS $$PWD/include;"

