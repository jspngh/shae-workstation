#-------------------------------------------------
#
# Project created by QtCreator 2016-03-10T11:36:49
#
#-------------------------------------------------

QT       -= core gui

TARGET = detection
TEMPLATE = lib
CONFIG +=   staticlib
CONFIG +=   c++11
# QMAKE_CXXFLAGS += -std=c++11

DEFINES += DETECTION_LIB

DESTDIR = $$PWD/bin
OBJECTS_DIR = $$PWD/build/

INCLUDEPATH += /usr/local/include/
INCLUDEPATH += /usr/local/include/opencv2

# LIBS += -L"/usr/local/lib" -lopencv_core -lopencv_objdetect -lopencv_highgui -lopencv_imgproc
CONFIG += link_pkgconfig
PKGCONFIG += opencv

SOURCES += \
    $$PWD/core/*.cpp \
    $$PWD/detection/*.cpp \
    $$PWD/detection/detectors/HOG/*.cpp \
    $$PWD/detection/detectors/ACF/*.cpp \
    $$PWD/detection/suppression/*.cpp \
    $$PWD/detection/window_selection/*.cpp \
    $$PWD/utils/*.cpp \

HEADERS += \
    $$PWD/core/*.h \
    $$PWD/detection/*.h \
    $$PWD/detection/detectors/HOG/*.h \
    $$PWD/detection/detectors/ACF/*.h \
    $$PWD/detection/suppression/*.h \
    $$PWD/detection/window_selection/*.h \
    $$PWD/utils/*.h \



