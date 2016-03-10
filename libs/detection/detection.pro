#-------------------------------------------------
#
# Project created by QtCreator 2016-03-10T11:36:49
#
#-------------------------------------------------

QT       -= core gui

TARGET = detection
TEMPLATE = lib
CONFIG += staticlib

SOURCES += detection.cpp

HEADERS += detection.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
