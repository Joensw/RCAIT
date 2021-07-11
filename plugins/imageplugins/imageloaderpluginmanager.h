#ifndef IMAGELOADERPLUGINMANAGER_H
#define IMAGELOADERPLUGINMANAGER_H


#include <QString>
#include <QWidget>
#include <pluginusage/progressableplugin.h>
#include "pluginmanager.h"

//Todo: Check singleton correctness
//Todo: Implement PluginManager interface
class ImageLoaderPluginManager : public PluginManager{
private:
    ImageLoaderPluginManager();

public:
    //Threadsafe singleton pattern
    ImageLoaderPluginManager(ImageLoaderPluginManager const &) = delete;
    void operator=(ImageLoaderPluginManager const &) = delete;

    static ImageLoaderPluginManager &getInstance() {
        static ImageLoaderPluginManager instance; // Guaranteed to be destroyed.
        // Instantiated on first use.
        return instance;
    }

    void loadPlugins(QString pluginDir);
    QWidget* getConfigurationWidget(QString pluginName);
    void saveConfiguration(QString pluginName);
    QWidget* getInputWidget(QString pluginName);
    bool loadImages(QString path, ProgressablePlugin* receiver, QString pluginName, int count, QStringList labels);
};


#endif //IMAGELOADERPLUGINMANAGER_H
