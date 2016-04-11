QT += core gui positioning testlib network sql

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
    core/detectioncontroller_test.h \
    core/searchdao_test.h \
    core/json_messages_test.h \
    core/detectioncontroller_test.h \
    core/polygonpathalgorithm_test.h \
    core/geopolygon_test.h \
    core/detectionresultdao_test.h \
    core/dronedao_test.h \
    core/dronesearchdao_test.h \
    core/dronestatusdao_test.h \
    core/videosequencedao_test.h \
    core/databasecreator.h\
    core/videocontroller_test.h \
    core/mediator_test.h \
    core/pathalgorithm_test.h \
    core/dronestatus_test.h \
    core/generaldao_test.h \
    core/xmlwriter_test.h


SOURCES += \
    core/simplepathalgorithm_test.cpp \
    core/json_messages_test.cpp \
    core/detectioncontroller_test.cpp \
    core/polygonpathalgorithm_test.cpp \
    core/geopolygon_test.cpp \
    main.cpp \
    core/searchdao_test.cpp \
    core/detectionresultdao_test.cpp \
    core/dronedao_test.cpp \
    core/dronesearchdao_test.cpp \
    core/dronestatusdao_test.cpp \
    core/videosequencedao_test.cpp \
    core/databasecreator.cpp \
    core/videocontroller_test.cpp \
    core/mediator_test.cpp \
    core/pathalgorithm_test.cpp \
    core/dronestatus_test.cpp \
    core/generaldao_test.cpp \
    core/xmlwriter_test.cpp


# c++11
CONFIG += c++11
QMAKE_CXXFLAGS += -std=c++11


# Code coverage
LIBS += -lgcov
QMAKE_CXXFLAGS += -g -fprofile-arcs -ftest-coverage -O0
QMAKE_LFLAGS += -g -fprofile-arcs -ftest-coverage  -O0


QMAKE

RESOURCES += \
    testApplication.qrc
