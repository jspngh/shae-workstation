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
CONFIG+=link_pkgconfig
PKGCONFIG+=opencv
# LIBS += -L"/usr/local/lib" -lopencv_nonfree -lopencv_core -lopencv_highgui -lopencv_objdetect -lopencv_imgproc -lopencv_ocl -lopencv_video -lopencv_photo -lopencv_ml -lopencv_features2d

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



