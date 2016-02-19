INCLUDEPATH += "ui"
DEPENDPATH += "ui"

SOURCES += ui/mainwindow.cpp
HEADERS += ui/mainwindow.h
FORMS += ui/mainwindow.ui \
    $$PWD/overviewwindow.ui

DISTFILES += \
    $$PWD/OverviewwindowForm.ui.qml \
    $$PWD/Overviewwindow.qml

RESOURCES += \
    $$PWD/mapplaceholder.qrc

