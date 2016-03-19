<<<<<<< HEAD
QT += testlib sql
=======

QT += core gui widgets positioning testlib network

>>>>>>> develop

TEMPLATE = app
TARGET = integration_tests

include(../../common.pri)

INCLUDEPATH += .
INCLUDEPATH += ../../src

DESTDIR = $$PWD/../../bin/tests/
OBJECTS_DIR = $$PWD/build/.obj
MOC_DIR = $$PWD/build/.moc
RCC_DIR = $$PWD/build/.qrc
UI_DIR = $$PWD/build/.ui


# Input
HEADERS += \
    qtmapkit_test.h

SOURCES += \
    qtmapkit_test.cpp

# c++11
CONFIG += c++11
QMAKE_CXXFLAGS += -std=c++11

include(../../src/core/core.pri)
include(../../src/ui/ui.pri)

