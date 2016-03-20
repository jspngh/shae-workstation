
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
    $$PWD/core/simplepathalgorithm_test.h \
    $$PWD/core/detectioncontroller_test.h \
    $$PWD/core/videocontroller_test.h \
    $$PWD/core/json_messages_test.h

SOURCES += \
    $$PWD/core/simplepathalgorithm_test.cpp \
    $$PWD/core/detectioncontroller_test.cpp \
    $$PWD/core/videocontroller_test.cpp \
    $$PWD/core/json_messages_test.cpp \
    main.cpp


# c++11
CONFIG += c++11
QMAKE_CXXFLAGS += -std=c++11

#include(../../src/core/core.pri)

