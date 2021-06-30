QT       += core gui charts svg svgwidgets

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
    imagegallerytree.cpp \
    imagesection.cpp \
    main.cpp \
    mainwindow.cpp \
    model/pluginusage/aithread.cpp \
    model/pluginusage/classifiertrainer.cpp \
    model/pluginusage/imageloader.cpp \
    model/pluginusage/imagesearchthread.cpp \
    model/pluginusage/progressable.cpp \
    model/pluginusage/progressableplugin.cpp \
    model/pluginusage/trainingsthread.cpp \
    newmodeldialog.cpp \
    newprojectdialog.cpp \
    plugins/classificationresult.cpp \
    plugins/result.cpp \
    plugins/trainingresult.cpp \
    removemodeldialog.cpp \
    removeprojectdialog.cpp \
    staticlist.cpp \
    tags.cpp

HEADERS += \
    aspectratiolabel.h \
    customtabbar.h \
    customtabwidget.h \
    imagegallery.h \
    imagegallerytree.h \
    imagesection.h \
    mainwindow.h \
    model/pluginusage/aithread.h \
    model/pluginusage/classifiertrainer.h \
    model/pluginusage/imageloader.h \
    model/pluginusage/imagesearchthread.h \
    model/pluginusage/progressable.h \
    model/pluginusage/progressableplugin.h \
    model/pluginusage/trainingsthread.h \
    newmodeldialog.h \
    newprojectdialog.h \
    plugins/classificationresult.h \
    plugins/result.h \
    plugins/trainingresult.h \
    qinputcontrol_p.h \
    removemodeldialog.h \
    removeprojectdialog.h \
    staticlist.h \
    tags.hpp

FORMS += \
    imagesection.ui \
    mainwindow.ui \
    newmodeldialog.ui \
    newprojectdialog.ui \
    removemodeldialog.ui \
    removeprojectdialog.ui \
    staticlist.ui

TRANSLATIONS += \
    languages/ui-test_de_DE.ts \
    languages/ui-test_en_GB.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += UI_Icons.qrc \
    Images.qrc \
    ressources.qrc

DISTFILES += \
    languages/ui-test_de_DE.qm \
    languages/ui-test_en_GB.qm

DEFINES += PROJECT_PATH=\"\\\"$${_PRO_FILE_PWD_}/\\\"\"
