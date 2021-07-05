#ifndef RCAIT_IMAGELOADERPLUGINMANAGER_H
#define RCAIT_IMAGELOADERPLUGINMANAGER_H


#include <QString>
#include <QWidget>
#include <pluginusage/progressableplugin.h>
#include "pluginmanager.h"

//Todo: Check singleton correctness
//Todo: Implement PluginManager interface
class ImageLoaderPluginManager : public PluginManager{
private:
    ImageLoaderPluginManager();
    static volatile ImageLoaderPluginManager* instance;

public:
    void loadPlugins(QString pluginDir);
    ImageLoaderPluginManager* getInstance();
    QWidget* getConfigurationWidget(QString pluginName);
    void saveConfiguration(QString pluginName);
    QWidget* getInputWidget(QString pluginName);
    bool loadImages(QString path, ProgressablePlugin* receiver, QString pluginName, int count, QStringList labels);
};


#endif //RCAIT_IMAGELOADERPLUGINMANAGER_H
