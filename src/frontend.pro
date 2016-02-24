# QT constraints
QT  += core gui webkit
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets webkitwidgets

# Project properties
TARGET = frontend
TEMPLATE = app

# Libraries
LIBS += -L"../libs/bin/libqtmapkit.so.1.0.0" -lqtmapkit
INCLUDEPATH += "../libs/include/qtmapkit"

# Put all releases in build-folder
release: DESTDIR = build/release
debug: DESTDIR = build/debug

OBJECTS_DIR = $$DESTDIR/.obj
MOC_DIR = $$DESTDIR/.moc
RCC_DIR = $$DESTDIR/.qrc
UI_DIR = $$DESTDIR/.ui

# Main source
SOURCES += main.cpp

# Resources
RESOURCES = application.qrc

# Put subdirectories here
include(ui/ui.pri)
include(core/core.pri)

DISTFILES +=

