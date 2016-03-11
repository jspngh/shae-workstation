INCLUDEPATH += "core"
DEPENDPATH += "core"


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

