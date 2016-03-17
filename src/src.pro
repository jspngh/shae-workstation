# QT constraints
QT  += core gui webkit positioning
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets webkitwidgets

# Project properties
TARGET = frontend
TEMPLATE = app

CONFIG += c++11

# Put all releases in build-folder
release: DESTDIR = $$PWD/../bin/release
debug: DESTDIR = $$PWD/../bin/debug

OBJECTS_DIR = $$PWD/build/.obj
MOC_DIR = $$PWD/build/.moc
RCC_DIR = $$PWD/build/.qrc
UI_DIR = $$PWD/build/.ui

# Libraries
LIBS +=  \
    -L"$$PWD/../libs/qtmapkit/bin/" -lqtmapkit \
    -L"$$PWD/../libs/detection/bin/" -ldetection

INCLUDEPATH += \
    "$$PWD/../libs/qtmapkit/include/" \
    "$$PWD/../libs/detection/"

HEADERS += \
    $$PWD/core/*.h \
    $$PWD/communication/*.h \
    $$PWD/detection/*.h \
    $$PWD/models/*.h \
    $$PWD/pathlogic/*.h \
    $$PWD/persistence/*.h \
    $$PWD/utils/*.h \
    $$PWD/models/*.h \
    $$PWD/videocontroller/*.h

SOURCES += \
    $$PWD/core/*.cpp \
    $$PWD/communication/*.cpp \
    $$PWD/detection/*.cpp \
    $$PWD/models/*.cpp \
    $$PWD/pathlogic/*.cpp \
    $$PWD/persistence/*.cpp \
    $$PWD/utils/*.cpp \
    $$PWD/models/*.cpp \
    $$PWD/videocontroller/*.cpp \
    main.cpp

# Resources
RESOURCES = application.qrc

# Put subdirectories here
include(ui/ui.pri)
include(core/core.pri)
include(communication/communication.pri)

