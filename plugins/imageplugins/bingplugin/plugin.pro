#! [0]

CONFIG         += plugin
CONFIG         += file_copies
COPIES         += pythonScripts
QT             += widgets
INCLUDEPATH    += ../echowindow


pythonScripts.files += $$PWD/test.py
pythonScripts.files += $$PWD/flickrapi_photosearch.py
pythonScripts.path += $$OUT_PWD

test {

message(Test Build)

QT             += testlib

HEADERS         = \
    bingplugin.h \
    bingsettings.h \
    test/tst_flickrplugin.h
SOURCES         = \
    bingplugin.cpp \
    test/main.cpp \
    test/tst_flickrplugin.cpp \
    test/flickrsettings_mockup.cpp

FORMS += \
    bingsettings.ui

TARGET = demo-test

} else {

message(Normal Build)
TEMPLATE        = lib
HEADERS         = \
    bingplugin.h \
    bingsettings.h

SOURCES         = \
    bingplugin.cpp \
    bingsettings.cpp

TARGET          = $$qtLibraryTarget(echoplugin)
DESTDIR         = ../plugins
#! [0]

EXAMPLE_FILES = flickrplugin.json

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/tools/echoplugin/plugins

INSTALLS += target \



CONFIG += install_ok  # Do not cargo-cult this!

FORMS += \
    bingsettings.ui

}

DISTFILES +=



