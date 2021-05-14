QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17 static

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    AspectRatioLabel.cpp \
    customtabbar.cpp \
    customtabwidget.cpp \
    imagegallery.cpp \
    imagesection.cpp \
    main.cpp \
    mainwindow.cpp \
    tags.cpp

HEADERS += \
    aspectratiolabel.h \
    customtabbar.h \
    customtabwidget.h \
    imagegallery.h \
    imagesection.h \
    mainwindow.h \
    qinputcontrol_p.h \
    tags.hpp

FORMS += \
    imagegallery.ui \
    images.ui \
    imagesection.ui \
    mainwindow.ui

TRANSLATIONS += \
    ui-test_de_DE.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ../TabIcons.qrc \
    UI_Icons.qrc
