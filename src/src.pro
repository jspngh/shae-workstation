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
LIBS +=  -L"$$PWD/../libs/qtmapkit/bin/" -lqtmapkit
# LIBS +=  -L"$$PWD/../libs/detection/bin/" -ldetection

INCLUDEPATH += "$$PWD/../libs/qtmapkit/include/"
# INCLUDEPATH +=  "$$PWD/../libs/"
# INCLUDEPATH +=  "../libs/detection"

# DEPENDPATH += "$$PWD/../libs/detection"
# DEPENDPATH += "$$PWD/../libs/"

# CONFIG += link_pkgconfig
# PKGCONFIG += opencv
# opencv (think it must be possible to delete this library)
# INCLUDEPATH += /usr/local/include/
# INCLUDEPATH += /usr/local/include/opencv2

# LIBS += -L"/usr/local/lib" -lopencv_core -lopencv_objdetect -lopencv_highgui -lopencv_imgproc

# Main source
SOURCES += main.cpp

# Resources
RESOURCES = application.qrc

# Put subdirectories here
include(ui/ui.pri)
include(core/core.pri)

