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

INCLUDEPATH += /usr/local/include/opencv2

LIBS += -L/usr/local/lib -lopencv_core -lopencv_imgcodecs -lopencv_highgui

SOURCES += \
    $$PWD/core/*.cpp \
    $$PWD/detection/*.cpp \
    $$PWD/detection/detectors/HOG/*.cpp \
    $$PWD/detection/suppression/*.cpp \
    $$PWD/detection/window_selection/*.cpp \
    $$PWD/testframework/*.cpp \
    $$PWD/utils/*.cpp \

HEADERS += \
    $$PWD/core/*.h \
    $$PWD/detection/*.h \
    $$PWD/detection/detectors/HOG/*.h \
    $$PWD/detection/suppression/*.h \
    $$PWD/detection/window_selection/*.h \
    $$PWD/testframework/*.h \
    $$PWD/utils/*.h \


unix {
    target.path = /usr/lib
    INSTALLS += target
}




