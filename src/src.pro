# QT constraints
QT  += core gui webkit
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets webkitwidgets

# Project properties
TARGET = frontend
TEMPLATE = app

# Put all releases in build-folder
release: DESTDIR = $$PWD/../bin/release
debug: DESTDIR = $$PWD/../bin/debug

OBJECTS_DIR = $$PWD/../build/bin/.obj
MOC_DIR = $$PWD/../build/bin/.moc
RCC_DIR = $$PWD/../build/bin/.qrc
UI_DIR = $$PWD/../build/bin/.ui

# Libraries
LIBS += \
    -L"$$PWD/../bin/lib/" -lqtmapkit
INCLUDEPATH += \
    "$$PWD/../build/include"

# Main source
SOURCES += main.cpp

# Resources
RESOURCES = application.qrc

# Put subdirectories here
include(ui/ui.pri)
include(core/core.pri)

DISTFILES +=

