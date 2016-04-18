QT += core gui widgets positioning testlib network sql


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
    core/qtmapkit_test.h \
    core/droneheartbeat_integrationtest.h \
    core/dronemodule_integrationtest.h \
    core/droneconnection_integrationtest.h \
    core/simulatorwrapper.h \
    core/system_test.h \
    core/databasecreator.h \
    core/signalslot_persistence_test.h

SOURCES += \
    core/qtmapkit_test.cpp \
    main.cpp \
    core/droneheartbeat_integrationtest.cpp \
    core/dronemodule_integrationtest.cpp \
    core/droneconnection_integrationtest.cpp \
    core/simulatorwrapper.cpp \
    core/system_test.cpp \
    core/databasecreator.cpp \
    core/signalslot_persistence_test.cpp

# c++11
CONFIG += c++11
QMAKE_CXXFLAGS += -std=c++11

# Code coverage
LIBS += -lgcov
QMAKE_CXXFLAGS += -g -fprofile-arcs -ftest-coverage -O0
QMAKE_LFLAGS += -g -fprofile-arcs -ftest-coverage  -O0

include(../../src/ui/ui.pri)
include(../../src/core/core.pri)

RESOURCES += \
    integrationtestapplication.qrc

