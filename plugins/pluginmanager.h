#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <QTextStream>
#include <QWidget>

/**
 * @brief The PluginManager class is the interface for all plugin managers.
 *
 */
class PluginManager {

public:

    /**
     * @brief getConfigurationWidget gets config widget of specified plugin.
     *
     * @param pluginName name of plugin
     * @return configuration widget of plugin
     */
    virtual QWidget* getConfigurationWidget(QString pluginName) = 0;

    /**
     * @brief loadPlugins loads plugins from a directory.
     *
     * @param pluginDir dir to load
     */
    virtual void loadPlugins(QString pluginDir) = 0;

    /**
     * @brief getInputWidget gets input widget of specified plugin.
     *
     * @param pluginName name of plugin
     * @return input widget of plugin
     */
    virtual QWidget* getInputWidget(QString pluginName) = 0;

    /**
     * @brief getNamesOfPlugins gets names of all loaded plugins.
     *
     * @return list of loaded plugins.
     */
    virtual QStringList getNamesOfPlugins() = 0;

    /**
     * @brief saveConfiguration saves configuration of specified plugin.
     *
     * @param pluginName name of plugin
     */
    virtual void saveConfiguration(QString pluginName) = 0;

};


#endif //PLUGINMANAGER_H
