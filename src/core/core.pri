INCLUDEPATH += "core"
DEPENDPATH += "core"


INCLUDEPATH += /usr/local/include/
INCLUDEPATH += /usr/local/include/opencv2
CONFIG+=link_pkgconfig
PKGCONFIG+=opencv
# LIBS += -L"/usr/local/lib" -lopencv_nonfree -lopencv_core -lopencv_highgui -lopencv_objdetect -lopencv_imgproc -lopencv_ocl -lopencv_video -lopencv_photo -lopencv_ml -lopencv_features2d


# If something has changed in libdetection: first rebuild the lib and then build the application
PRE_TARGETDEPS += "$$PWD/../../libs/detection/bin/libdetection.a"

