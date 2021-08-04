#ifndef FOLDERPLUGIN_H
#define FOLDERPLUGIN_H



#include "folderconfigwidget.h"

#include "../imageloaderplugin.h"
#include "../plugin.h"
#include "../../../model/pluginusage/progressableplugin.h"
#include <QDir>
#include <QObject>
#include <QtWidgets/QWidget>
#include <QtPlugin>



class FolderPlugin : public QObject, ImageLoaderPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "de.Fraunhofer.IOSB.RCAIT.FolderPlugin" FILE "FolderPlugin.json")
    Q_INTERFACES(ImageLoaderPlugin)
public:

    bool loadImages(const QString path, ProgressablePlugin *receiver, const int imageCount, const QStringList label) override;
    QWidget *getConfigurationWidget() override;

    void saveConfiguration() override;
    void init() override;

    QString getName() override;
    QWidget*  getInputWidget() override;


private:
    FolderConfigwidget* mConfigWidget;
    int mode = 0;
    QString imageDir;
    bool addLabel(QStringList list, QDir in, QDir out);

};

#endif // FOLDERPLUGIN_H
