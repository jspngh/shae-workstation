INCLUDEPATH += "core"
DEPENDPATH += "core"

CONFIG += c++11

LIBS +=  -L"$$PWD/../../libs/detection/bin/" -ldetection
INCLUDEPATH +=  "$$PWD/../../libs/"

INCLUDEPATH += /usr/local/include/
INCLUDEPATH += /usr/local/include/opencv2
CONFIG+=link_pkgconfig
PKGCONFIG+=opencv
# LIBS += -L"/usr/local/lib" -lopencv_nonfree -lopencv_core -lopencv_highgui -lopencv_objdetect -lopencv_imgproc -lopencv_ocl -lopencv_video -lopencv_photo -lopencv_ml -lopencv_features2d


SOURCES += \
    $$PWD/controller.cpp \
    $$PWD/drone.cpp \
    $$PWD/simplepathalgorithm.cpp \
    $$PWD/pathalgorithm.cpp \
    $$PWD/detectioncontroller.cpp \
    $$PWD/utils/queue.cpp \
    $$PWD/mediator.cpp

HEADERS += \
    $$PWD/controller.h \
    $$PWD/drone.h \
    $$PWD/pathalgorithm.h \
    $$PWD/simplepathalgorithm.h \
    $$PWD/mediator.h \
    $$PWD/detectioncontroller.h \
    $$PWD/utils/queue.h

# If something has changed in libdetection: first rebuild the lib and then build the application
PRE_TARGETDEPS += "$$PWD/../../libs/detection/bin/libdetection.a"

