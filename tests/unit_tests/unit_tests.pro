
QT += core gui positioning testlib network


TEMPLATE = app
TARGET = unit_tests

include(../../common.pri)
include(../../src/ui/ui.pri)

INCLUDEPATH += .
INCLUDEPATH += ../../src

DESTDIR = $$PWD/../../bin/tests/
OBJECTS_DIR = $$PWD/build/.obj
MOC_DIR = $$PWD/build/.moc
RCC_DIR = $$PWD/build/.qrc
UI_DIR = $$PWD/build/.ui

# Input
HEADERS += \
    core/simplepathalgorithm_test.h \
    core/json_messages_test.h \
    core/detectioncontroller_test.h \
    core/videocontroller_test.h \
    core/mediator_test.h

SOURCES += \
    core/simplepathalgorithm_test.cpp \
    core/json_messages_test.cpp \
    core/detectioncontroller_test.cpp \
    core/videocontroller_test.cpp \
    core/mediator_test.cpp \
    main.cpp

# c++11
CONFIG += c++11
QMAKE_CXXFLAGS += -std=c++11

#include(../../src/core/core.pri)

