QT += core gui positioning testlib widgets

TEMPLATE = app
TARGET = unit_tests
INCLUDEPATH += "."
INCLUDEPATH += "./core"
INCLUDEPATH += "../../src"

DESTDIR = $$PWD/../../bin/tests/
OBJECTS_DIR = $$PWD/build/.obj
MOC_DIR = $$PWD/build/.moc
RCC_DIR = $$PWD/build/.qrc
UI_DIR = $$PWD/build/.ui

# run main of unit test after build
# QMAKE_POST_LINK = ./$${DESTDIR}/$${TARGET}

# Input
HEADERS += \
    core/simplepathalgorithm_test.h \
    core/detectioncontroller_test.h \
    core/videocontroller_test.h

SOURCES += \
    core/simplepathalgorithm_test.cpp \
    core/detectioncontroller_test.cpp \
    core/videocontroller_test.cpp \
    main.cpp


include(../../src/core/core.pri)

