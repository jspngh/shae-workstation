INCLUDEPATH += "core"
DEPENDPATH += "core"

CONFIG += c++11

LIBS +=  -L"$$PWD/../../libs/detection/bin/" -ldetection
LIBS += -lvlc
INCLUDEPATH +=  "$$PWD/../../libs/"

INCLUDEPATH += /usr/local/include/
INCLUDEPATH += /usr/local/include/opencv2
CONFIG+=link_pkgconfig
PKGCONFIG+=opencv
# LIBS += -L"/usr/local/lib" -lopencv_nonfree -lopencv_core -lopencv_highgui -lopencv_objdetect -lopencv_imgproc -lopencv_ocl -lopencv_video -lopencv_photo -lopencv_ml -lopencv_features2d


SOURCES += \
    $$PWD/communication/*.cpp \
    $$PWD/detection/*.cpp \
    $$PWD/models/*.cpp \
    $$PWD/pathlogic/*.cpp \
    $$PWD/persistence/*.cpp \
    $$PWD/utils/*.cpp \
    $$PWD/persistence/persistence.cpp \
    $$PWD/models/dronestatus.cpp \
    $$PWD/models/videosequence.cpp \
    $$PWD/models/detectionresult.cpp \
    $$PWD/models/search.cpp \
    $$PWD/videocontroller/videocontroller.cpp


HEADERS += \
    $$PWD/communication/*.h \
    $$PWD/detection/*.h \
    $$PWD/models/*.h \
    $$PWD/pathlogic/*.h \
    $$PWD/persistence/*.h \
    $$PWD/utils/*.h \
    $$PWD/persistence/persistence.h \
    $$PWD/models/dronestatus.h \
    $$PWD/models/videosequence.h \
    $$PWD/models/detectionresult.h \
    $$PWD/models/search.h \
    $$PWD/videocontroller/videocontroller.h
# If something has changed in libdetection: first rebuild the lib and then build the application
PRE_TARGETDEPS += "$$PWD/../../libs/detection/bin/libdetection.a"



