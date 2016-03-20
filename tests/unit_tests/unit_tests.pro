QT += core gui positioning testlib network sql

TEMPLATE = app
TARGET = unit_tests

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
    core/simplepathalgorithm_test.h \
    core/detectioncontroller_test.h \
    core/searchdao_test.h \
    core/json_messages_test.h \
    core/detectioncontroller_test.h \
    core/detectionresultdao_test.h \
    core/dronedao_test.h \
    core/dronesearchdao_test.h \
    core/dronestatusdao_test.h \
    core/videosequencedao_test.h

SOURCES += \
    core/simplepathalgorithm_test.cpp \
    core/json_messages_test.cpp \
    core/detectioncontroller_test.cpp \
    main.cpp \
    core/searchdao_test.cpp \
    core/detectionresultdao_test.cpp \
    core/dronedao_test.cpp \
    core/dronesearchdao_test.cpp \
    core/dronestatusdao_test.cpp \
    core/videosequencedao_test.cpp


# c++11
CONFIG += c++11
QMAKE_CXXFLAGS += -std=c++11

include(../../src/ui/ui.pri)
include(../../src/core/core.pri)

