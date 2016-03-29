
QT += core gui positioning testlib network


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
    core/json_messages_test.h \
    core/detectioncontroller_test.h \
    core/mediator_test.h \
    core/polygonpathalgorithm_test.h \
    core/geopolygon_test.h

SOURCES += \
    core/simplepathalgorithm_test.cpp \
    core/json_messages_test.cpp \
    core/detectioncontroller_test.cpp \
    main.cpp \
    core/mediator_test.cpp \
    core/polygonpathalgorithm_test.cpp \
    core/geopolygon_test.cpp


# c++11
CONFIG += c++11
QMAKE_CXXFLAGS += -std=c++11

# Code coverage
LIBS += -lgcov
QMAKE_CXXFLAGS += -g -fprofile-arcs -ftest-coverage -O0
QMAKE_LFLAGS += -g -fprofile-arcs -ftest-coverage  -O0

include(../../src/ui/ui.pri)
include(../../src/core/core.pri)

