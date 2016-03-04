QT += core gui positioning testlib

TEMPLATE = app
TARGET = integration_tests
INCLUDEPATH += .
INCLUDEPATH += ../../src

DESTDIR = $$PWD/../../bin/tests/
OBJECTS_DIR = $$PWD/build/.obj
MOC_DIR = $$PWD/build/.moc
RCC_DIR = $$PWD/build/.qrc
UI_DIR = $$PWD/build/.ui

# Input
SOURCES += qtmapkit_test.cpp
include(../../src/core/core.pri)

