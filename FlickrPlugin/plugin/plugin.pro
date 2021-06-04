#! [0]
TEMPLATE        = lib
CONFIG         += plugin
QT             += widgets
INCLUDEPATH    += ../echowindow
HEADERS         = echoplugin.h \
    flickrsettings.h
SOURCES         = echoplugin.cpp \
    flickrsettings.cpp
TARGET          = $$qtLibraryTarget(echoplugin)
DESTDIR         = ../plugins
#! [0]

EXAMPLE_FILES = echoplugin.json

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/tools/echoplugin/plugins
INSTALLS += target

CONFIG += install_ok  # Do not cargo-cult this!

FORMS += \
    flickrsettings.ui
