#-------------------------------------------------
#
# Project created by QtCreator 2016-02-14T18:06:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Workstation_project_shae
TEMPLATE = app

release: DESTDIR = build/release
debug: DESTDIR = build/debug

SOURCES += main.cpp

RESOURCES = application.qrc

include(ui/ui.pri)

