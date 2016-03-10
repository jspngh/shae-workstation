QT += core gui positioning testlib webkit
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets webkitwidgets

TEMPLATE = app
TARGET = unit_tests
INCLUDEPATH += .
INCLUDEPATH += ../../src

DESTDIR = $$PWD/../../bin/tests/
OBJECTS_DIR = $$PWD/build/.obj
MOC_DIR = $$PWD/build/.moc
RCC_DIR = $$PWD/build/.qrc
UI_DIR = $$PWD/build/.ui

# Libraries
LIBS += \
    -L"$$PWD/../../libs/qtmapkit/bin/" -lqtmapkit
INCLUDEPATH += \
    "$$PWD/../../libs/qtmapkit/include/"

# Input
HEADERS += \
    core/simplepathalgorithm_test.h

SOURCES += \
    core/simplepathalgorithm_test.cpp


include(../../src/ui/ui.pri)
include(../../src/core/core.pri)

