INCLUDEPATH += "core"
DEPENDPATH += "core"

CONFIG += c++11

LIBS +=  -L"$$PWD/../../libs/detection/bin/" -ldetection
INCLUDEPATH +=  "$$PWD/../../libs/"

INCLUDEPATH += /usr/local/include/
LIBS += -L"/usr/local/lib" -lopencv_core -lopencv_objdetect -lopencv_highgui -lopencv_imgproc

SOURCES += $$PWD/communication.cpp \
    $$PWD/drone.cpp \
    $$PWD/simplepathalgorithm.cpp \
    $$PWD/pathalgorithm.cpp \
    $$PWD/detectioncontroller.cpp \
    $$PWD/utils/queue.cpp

HEADERS += $$PWD/communication.h \
    $$PWD/drone.h \
    $$PWD/pathalgorithm.h \
    $$PWD/simplepathalgorithm.h \
    $$PWD/detectioncontroller.h \
    $$PWD/utils/queue.h




