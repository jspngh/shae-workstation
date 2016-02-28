#-------------------------------------------------
#
# Project created by QtCreator 2016-02-14T18:06:46
#
#-------------------------------------------------

# QT constraints
QT  += core gui
QT  += positioning
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# Project properties
TARGET = frontend
TEMPLATE = app

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

