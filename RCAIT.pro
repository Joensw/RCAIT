QT       += core gui charts svg svgwidgets

INCLUDEPATH += view

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17 static

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    controller/aicontroller.cpp \
    controller/settingscontroller.cpp \
    model/pluginusage/aithread.cpp \
    model/pluginusage/classifiertrainer.cpp \
    model/pluginusage/imageloader.cpp \
    model/pluginusage/imagesearchthread.cpp \
    model/pluginusage/progressable.cpp \
    model/pluginusage/progressableplugin.cpp \
    model/pluginusage/trainingsthread.cpp \
    plugins/classificationresult.cpp \
    plugins/result.cpp \
    plugins/trainingresult.cpp \
    view/AspectRatioLabel.cpp \
    view/customtabbar.cpp \
    view/customtabwidget.cpp \
    view/imagegallery.cpp \
    view/imagegallerytree.cpp \
    view/imagesection.cpp \
    view/inputimageswidget.cpp \
    view/main.cpp \
    view/mainwindow.cpp \
    view/newmodeldialog.cpp \
    view/newprojectdialog.cpp \
    view/removemodeldialog.cpp \
    view/removeprojectdialog.cpp \
    view/settingsview.cpp \
    view/staticlist.cpp \
    view/tags.cpp

HEADERS += \
    controller/aicontroller.h \
    controller/settingscontroller.h \
    model/pluginusage/aithread.h \
    model/pluginusage/classifiertrainer.h \
    model/pluginusage/imageloader.h \
    model/pluginusage/imagesearchthread.h \
    model/pluginusage/progressable.h \
    model/pluginusage/progressableplugin.h \
    model/pluginusage/trainingsthread.h \
    plugins/classificationresult.h \
    plugins/result.h \
    plugins/trainingresult.h \
    view/aspectratiolabel.h \
    view/customtabbar.h \
    view/customtabwidget.h \
    view/imagegallery.h \
    view/imagegallerytree.h \
    view/imagesection.h \
    view/inputimageswidget.h \
    view/mainwindow.h \
    view/newmodeldialog.h \
    view/newprojectdialog.h \
    view/qinputcontrol_p.h \
    view/removemodeldialog.h \
    view/removeprojectdialog.h \
    view/settingsview.h \
    view/staticlist.h \
    view/tags.hpp

FORMS += \
    imagesection.ui \
    mainwindow.ui \
    newmodeldialog.ui \
    newprojectdialog.ui \
    removemodeldialog.ui \
    removeprojectdialog.ui \
    staticlist.ui \
    view/inputimageswidget.ui

TRANSLATIONS += \
    languages/RCAIT_de_DE.ts \
    languages/RCAIT_en_GB.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
	UI_Icons.qrc \
    Images.qrc \
    ressources.qrc

DISTFILES += \
    languages/RCAIT_de_DE.qm \
    languages/RCAIT_en_GB.qm

DEFINES += PROJECT_PATH=\"\\\"$${_PRO_FILE_PWD_}/\\\"\"
