# common build options for src and tests
# QT constraints
QT  += core gui webkit positioning
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets webkitwidgets

CONFIG += c++11
INCLUDEPATH += /usr/local/include/
INCLUDEPATH += /usr/local/include/opencv2
CONFIG+=link_pkgconfig
PKGCONFIG+=opencv
# Libraries
LIBS +=  \
    -L"$$PWD/libs/qtmapkit/bin/" -lqtmapkit \
    -L"$$PWD/libs/detection/bin/" -ldetection
LIBS += -lvlc


INCLUDEPATH += \
    "$$PWD/libs/qtmapkit/include/" \
    "$$PWD/libs/detection/"

HEADERS += \
    $$PWD/src/communication/*.h \
    $$PWD/src/core/*.h \
    $$PWD/src/detection/*.h \
    $$PWD/src/models/*.h \
    $$PWD/src/pathlogic/*.h \
    $$PWD/src/persistence/*.h \
    $$PWD/src/videocontroller/*.h

SOURCES += \
    $$PWD/src/communication/*.cpp \
    $$PWD/src/core/*.cpp \
    $$PWD/src/detection/*.cpp \
    $$PWD/src/models/*.cpp \
    $$PWD/src/pathlogic/*.cpp \
    $$PWD/src/persistence/*.cpp \
    $$PWD/src/videocontroller/*.cpp
