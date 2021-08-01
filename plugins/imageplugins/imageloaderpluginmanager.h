#ifndef IMAGELOADERPLUGINMANAGER_H
#define IMAGELOADERPLUGINMANAGER_H


#include <QString>
#include <QWidget>
#include <pluginusage/progressableplugin.h>
#include "pluginmanager.h"
#include "imageloaderplugin.h"
#include <QMap>
#include <QPluginLoader>
#include <QDir>

//Todo: Check singleton correctness
//Todo: Implement PluginManager interface
class ImageLoaderPluginManager : public PluginManager{
private:
    ImageLoaderPluginManager();
    QMap<QString, ImageLoaderPlugin*> m_plugins;
    QSharedPointer<ImageLoaderPlugin> test;
    QMap<QString, ImageLoaderPlugin*> m_pluginsSharedPointer;

public:
    //Threadsafe singleton pattern
    ImageLoaderPluginManager(ImageLoaderPluginManager const &) = delete;
    void operator=(ImageLoaderPluginManager const &) = delete;

    static ImageLoaderPluginManager &getInstance() {
        static ImageLoaderPluginManager instance; // Guaranteed to be destroyed.
        // Instantiated on first use.
        return instance;
    }

    void loadPlugins(QString pluginDir) override;
    QWidget* getConfigurationWidget(QString pluginName) override;
    void saveConfiguration(QString pluginName) override;
    QWidget* getInputWidget(QString pluginName) override;
    bool loadImages(QString path, ProgressablePlugin* receiver, QString pluginName, int count, QStringList labels);
    QStringList getNamesOfPlugins() override;
    QList<QWidget*> getConfigurationWidgets();
    QList<QWidget*> m_pluginConfigurationWidgets;
};


#endif //IMAGELOADERPLUGINMANAGER_H
