QT += sql

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
    main.cpp \

# Resources
RESOURCES = application.qrc

# Put subdirectories here
include(ui/ui.pri)
include(core/core.pri)


