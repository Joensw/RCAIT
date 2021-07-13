QT += widgets


test {
} else {



HEADERS    = echowindow.h \
             imageloaderplugin.h \
             mainwindow.h \
             settings.h
SOURCES    = echowindow.cpp \
             main.cpp \
             mainwindow.cpp \
             settings.cpp

TARGET     = echoplugin
QMAKE_PROJECT_NAME = echopluginwindow
win32 {
    CONFIG(debug, release|debug):DESTDIR = ../debug/
    CONFIG(release, release|debug):DESTDIR = ../release/
} else {
    DESTDIR    = ../
}

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/tools/echoplugin
INSTALLS += target

CONFIG += install_ok  # Do not cargo-cult this!

FORMS += \
    mainwindow.ui \
    settings.ui
}
