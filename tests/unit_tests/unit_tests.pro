QT += testlib sql

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
    core/searchdao_test.h

SOURCES += \
    core/simplepathalgorithm_test.cpp \
    core/detectioncontroller_test.cpp \
    main.cpp \
    core/searchdao_test.cpp


include(../../src/ui/ui.pri)
include(../../src/core/core.pri)

