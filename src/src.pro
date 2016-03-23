# QT constraints
# QT  += core gui network webkit positioning
# greaterThan(QT_MAJOR_VERSION, 4): QT += widgets webkitwidgets


# Project properties
TARGET = frontend
TEMPLATE = app

include(../common.pri)

# Put all releases in build-folder
release: DESTDIR = $$PWD/../bin/release
debug: DESTDIR = $$PWD/../bin/debug

OBJECTS_DIR = $$PWD/build/.obj
MOC_DIR = $$PWD/build/.moc
RCC_DIR = $$PWD/build/.qrc
UI_DIR = $$PWD/build/.ui

SOURCES += \
    main.cpp


# c++11
CONFIG += c++11
QMAKE_CXXFLAGS += -std=c++11

# Resources
RESOURCES = application.qrc

# Put subdirectories here
include(ui/ui.pri)
include(core/core.pri)




