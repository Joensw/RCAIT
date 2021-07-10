#! [0]
TEMPLATE        = lib
CONFIG         += plugin
QT             += widgets
INCLUDEPATH    += ../echowindow
HEADERS         = \
    flickrplugin.h \
    flickrsettings.h \
    test/tst_flickrplugin.h
SOURCES         = \
    flickrplugin.cpp \
    flickrsettings.cpp \
    test/tst_flickrplugin.cpp
TARGET          = $$qtLibraryTarget(echoplugin)
DESTDIR         = ../plugins
#! [0]

EXAMPLE_FILES = flickrplugin.json

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/tools/echoplugin/plugins
INSTALLS += target

CONFIG += install_ok  # Do not cargo-cult this!

FORMS += \
    flickrsettings.ui
