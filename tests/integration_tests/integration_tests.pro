QT += core gui widgets positioning testlib network

TEMPLATE = app
TARGET = integration_tests
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
    qtmapkit_test.h

SOURCES += \
    qtmapkit_test.cpp

# c++11
CONFIG += c++11
QMAKE_CXXFLAGS += -std=c++11

include(../../src/core/core.pri)

