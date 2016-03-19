QT += testlib sql

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


include(../../src/core/core.pri)
include(../../src/ui/ui.pri)

