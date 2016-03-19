INCLUDEPATH += "core"
DEPENDPATH += "core"

#<<<<<<< Communication when merging
#SOURCES += $$PWD/communication.cpp \
#    $$PWD/drone.cpp \
#    $$PWD/simplepathalgorithm.cpp \
#    $$PWD/pathalgorithm.cpp \
#    $$PWD/droneconnection.cpp \
#    $$PWD/dronestatus.cpp \
#    $$PWD/parseexception.cpp
#HEADERS += $$PWD/communication.h \
#    $$PWD/drone.h \
#    $$PWD/pathalgorithm.h \
#    $$PWD/simplepathalgorithm.h \
#    $$PWD/droneconnection.h \
#    $$PWD/dronestatus.h \
#    $$PWD/parseexception.h
#=======

INCLUDEPATH += /usr/local/include/
INCLUDEPATH += /usr/local/include/opencv2
CONFIG+=link_pkgconfig
PKGCONFIG+=opencv
# LIBS += -L"/usr/local/lib" -lopencv_nonfree -lopencv_core -lopencv_highgui -lopencv_objdetect -lopencv_imgproc -lopencv_ocl -lopencv_video -lopencv_photo -lopencv_ml -lopencv_features2d


# If something has changed in libdetection: first rebuild the lib and then build the application
PRE_TARGETDEPS += "$$PWD/../../libs/detection/bin/libdetection.a"


