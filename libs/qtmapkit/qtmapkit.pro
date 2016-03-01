QT       += webkit positioning
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets webkitwidgets

TARGET = qtmapkit
TEMPLATE = lib
CONFIG += staticlib

DEFINES += QTMAPKIT_LIBRARY

DESTDIR = $$PWD/bin
OBJECTS_DIR = $$PWD/build/
MOC_DIR = $$PWD/build/
RCC_DIR = $$PWD/build/
UI_DIR = $$PWD/build/

SOURCES += \
    $$PWD/src/QMMapView.cpp

HEADERS += \
    $$PWD/src/QtMapKit.h \
    $$PWD/src/qtmapkit_global.h \
    $$PWD/src/QMMapView.h \

RESOURCES += \
    $$PWD/src/qtmapkit_resources.qrc

OTHER_FILES += \
    $$PWD/src/gmap.html \
    $$PWD/src/gmap.js

# Copy headers to include-folder
QMAKE_EXTRA_TARGETS += public_headers
POST_TARGETDEPS += public_headers
INCLUDEDIR = \"$${PWD}/include\"

win32 {
    INCLUDEDIR_WIN = $${INCLUDEDIR}
    INCLUDEDIR_WIN ~= s,/,\\,g
    public_headers.commands += $$quote(cmd /c if not exist $${INCLUDEDIR_WIN} mkdir $${INCLUDEDIR_WIN}$$escape_expand(\\n\\t))
    for(HEADER, HEADERS) {
        HEADER_WIN = \"$${HEADER}\"
        HEADER_WIN ~= s,/,\\,g
        public_headers.commands += $$quote(cmd /c copy /y $${HEADER_WIN} $${INCLUDEDIR_WIN}$$escape_expand(\\n\\t))
    }
}
unix {
    for(HEADER, HEADERS) {
        HEADER_UNIX = \"$${HEADER}\"
        public_headers.commands += $$quote(mkdir -p $${INCLUDEDIR}$$escape_expand(\\n\\t))
        public_headers.commands += $$quote(cp $${HEADER_UNIX} $${INCLUDEDIR}$$escape_expand(\\n\\t))
    }
}
