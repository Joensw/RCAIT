QT       += core gui svg svgwidgets

INCLUDEPATH += \
    model \
        model\automation \
        model\pluginusage \
        model\results \
    view \
        view\imageinspection \
        view\results \
    controller \
    plugins \
        plugins\imageplugins \
        plugins\results \
        plugins\classificationplugins

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17 static

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    controller/aicontroller.cpp \
    controller/automationcontroller.cpp \
    controller/configurationcontroller.cpp \
    controller/modelcontroller.cpp \
    controller/projectcontroller.cpp \
    controller/controller.cpp \
    controller/settingscontroller.cpp \
    controller/resultscontroller.cpp \
    model/datamanager.cpp \
    model/automation/addprojectcommand.cpp \
    model/automation/automator.cpp \
    model/automation/command.cpp \
    model/automation/classificationcommand.cpp \
    model/automation/imageloadcommand.cpp \
    model/automation/task.cpp \
    model/automation/trainingcommand.cpp \
    model/modelmanager.cpp \
    model/pluginusage/aithread.cpp \
    model/pluginusage/classifiertrainer.cpp \
    model/pluginusage/imageloader.cpp \
    model/pluginusage/imagesearchthread.cpp \
    model/pluginusage/classificationthread.cpp \
    model/pluginusage/progressable.cpp \
    model/pluginusage/progressableplugin.cpp \
    model/pluginusage/trainingsthread.cpp \
    model/projectmanager.cpp \
    model/results/abstractresultgraphics.cpp \
    model/results/confusionmatrix.cpp \
    model/results/losscurve.cpp \
    model/settingsmanager.cpp \
    plugins/classificationplugins/classificationplugin.cpp \
    plugins/classificationplugins/classificationpluginmanager.cpp \
    plugins/imageplugins/imageloaderplugin.cpp \
    plugins/imageplugins/imageloaderpluginmanager.cpp \
    plugins/plugin.cpp \
    plugins/pluginmanager.cpp \
    plugins/results/classificationresult.cpp \
    plugins/results/result.cpp \
    plugins/results/trainingresult.cpp \
    view/aitrainingwidget.cpp \
    view/aspectratiolabel.cpp \
    view/automationwidget.cpp \
    view/configurationdialog.cpp \
    view/customlistwidget.cpp \
    view/customtabbar.cpp \
    view/customtabwidget.cpp \
    view/globalsettingswidget.cpp \
    view/imagegallery.cpp \
    view/imagegallerytree.cpp \
    view/imagesection.cpp \
    view/importfileswidget.cpp \
    view/inputimageswidget.cpp \
    view/main.cpp \
    view/mainwindow.cpp \
    view/newmodeldialog.cpp \
    view/newprojectdialog.cpp \
    view/removemodeldialog.cpp \
    view/removeprojectdialog.cpp \
    view/results/canvas.cpp \
    view/results/resultswidget.cpp \
    view/results/topaccuraciesview.cpp \
    view/results/trainingresultview.cpp \
    view/settingsview.cpp \
    view/startwidget.cpp \
    view/staticlist.cpp \
    view/tags.cpp

HEADERS += \
    controller/aicontroller.h \
    controller/automationcontroller.h \
    controller/configurationcontroller.h \
    controller/modelcontroller.h \
    controller/projectcontroller.h \
    controller/controller.h \
    controller/settingscontroller.h \
    controller/resultscontroller.h \
    model/datamanager.h \
    model/automation/addprojectcommand.h \
    model/automation/automator.h \
    model/automation/command.h \
    model/automation/classificationcommand.h \
    model/automation/imageloadcommand.h \
    model/automation/task.h \
    model/automation/trainingcommand.h \
    model/modelmanager.h \
    model/pluginusage/aithread.h \
    model/pluginusage/classifiertrainer.h \
    model/pluginusage/imageloader.h \
    model/pluginusage/imagesearchthread.h \
    model/pluginusage/classificationthread.h \
    model/pluginusage/progressable.h \
    model/pluginusage/progressableplugin.h \
    model/pluginusage/trainingsthread.h \
    model/projectmanager.h \
    model/results/abstractresultgraphics.h \
    model/results/confusionmatrix.h \
    model/results/losscurve.h \
    model/settingsmanager.h \
    plugins/classificationplugins/classificationplugin.h \
    plugins/classificationplugins/classificationpluginmanager.h \
    plugins/classificationresult.h \
    plugins/imageplugins/imageloaderplugin.h \
    plugins/imageplugins/imageloaderpluginmanager.h \
    plugins/plugin.h \
    plugins/pluginmanager.h \
    plugins/result.h \
    plugins/results/classificationresult.h \
    plugins/results/result.h \
    plugins/results/trainingresult.h \
    plugins/trainingresult.h \
    view/aitrainingwidget.h \
    view/aspectratiolabel.h \
    view/automationwidget.h \
    view/configurationdialog.h \
    view/customlistwidget.h \
    view/customtabbar.h \
    view/customtabwidget.h \
    view/globalsettingswidget.h \
    view/imagegallery.h \
    view/imagegallerytree.h \
    view/imagesection.h \
    view/importfileswidget.h \
    view/inputimageswidget.h \
    view/mainwindow.h \
    view/newmodeldialog.h \
    view/newprojectdialog.h \
    view/qinputcontrol_p.h \
    view/removemodeldialog.h \
    view/removeprojectdialog.h \
    view/results/abstractgraphicsview.h \
    view/results/canvas.h \
    view/results/resultswidget.h \
    view/results/topaccuraciesview.h \
    view/results/trainingresultview.h \
    view/settingsview.h \
    view/startwidget.h \
    view/staticlist.h \
    view/tags.hpp

FORMS += \
    configurationdialog.ui \
    globalsettingswidget.ui \
    imagesection.ui \
    importfileswidget.ui \
    mainwindow.ui \
    newmodeldialog.ui \
    newprojectdialog.ui \
    removemodeldialog.ui \
    removeprojectdialog.ui \
    resultswidget.ui \
    startwidget.ui \
    staticlist.ui \
    trainingresultview.ui \
    view/aitrainingwidget.ui \
    view/automationwidget.ui \
    view/inputimageswidget.ui \
    view/results/topaccuraciesview.ui \
    view/settingsview.ui

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
    languages/RCAIT_en_GB.qm \
    model/results/confusionmatrix.py

install_it.path = $$OUT_PWD
install_it.files = model/results/confusionmatrix.py

INSTALLS += \
    install_it

DEFINES += PROJECT_PATH=\"\\\"$${_PRO_FILE_PWD_}/\\\"\"
