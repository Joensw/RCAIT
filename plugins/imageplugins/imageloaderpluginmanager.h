/**
 * @file imageloaderpluginmanager.h
 *
 * @brief contains class ImagerLoaderPluginManager
 *
 */
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

/**
 * @brief The ImageLoaderPluginManager class is responsible for loading and managing image load plugins.
 *
 */
class ImageLoaderPluginManager : public PluginManager{

private:
    ImageLoaderPluginManager();
    QMap<QString, QSharedPointer<ImageLoaderPlugin>> m_plugins;
    QSharedPointer<ImageLoaderPlugin> test;
    QList<QSharedPointer<QWidget>> m_pluginConfigurationWidgets;

public:
    /**
     * @brief ImageLoaderPluginManager singleton constructor
     */
    ImageLoaderPluginManager(ImageLoaderPluginManager const &) = delete;
    /**
     * @brief operator = delete deleted assingment operator
     */
    void operator=(ImageLoaderPluginManager const &) = delete;

    /**
     * @brief getInstance gets singleton instance of ImagePluginManager.
     *
     * @return ImagePluginManager instance
     */
    static ImageLoaderPluginManager &getInstance() {
        static ImageLoaderPluginManager instance; // Guaranteed to be destroyed.
        // Instantiated on first use.
        return instance;
    }


    /**
     * @brief loadPlugins loads image plugins from a directory.
     *
     * @param pluginDir dir to load
     */
    void loadPlugins(QString pluginDir) override;

    /**
     * @brief getConfigurationWidget gets config widget of specified plugin.
     *
     * @param pluginName name of plugin
     * @return configuration widget of plugin
     */
    QSharedPointer<QWidget> getConfigurationWidget(QString pluginName) override;

    /**
     * @brief saveConfiguration saves configuration of specified plugin.
     *
     * @param pluginName name of plugin
     */
    void saveConfiguration(QString pluginName) override;

    /**
     * @brief getInputWidget gets input widget of specified plugin.
     *
     * @param pluginName name of plugin
     * @return input widget of plugin
     */
    QSharedPointer<QWidget> getInputWidget(QString pluginName) override;


    /**
     * @brief getNamesOfPlugins gets names of all loaded image plugins.
     *
     * @return list of loaded plugins.
     */
    QStringList getNamesOfPlugins() override;

    /**
     * @brief loadImages starts loading images with a selected plugin.
     *
     * @param path directory to load images to
     * @param receiver receives progress of image loading
     * @param pluginName name of selected plugin
     * @param count number of images loaded per label
     * @param labels list of image labels
     * @return true if loading was successful, false otherwise
     */
    bool loadImages(const QString &path, ProgressablePlugin *receiver, const QString &pluginName, int count,
                    const QStringList &labels);

    /**
     * @brief getConfigurationWidgets gets config widget of all loaded plugins.
     *
     * @return list of all config widgets
     */
    QList<QSharedPointer<QWidget>> getConfigurationWidgets();

};


#endif //IMAGELOADERPLUGINMANAGER_H
