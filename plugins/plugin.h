/**
 *
 * @file plugin.h
 *
 * @brief contains interface for plugins
 *
 */
#ifndef PLUGIN_H
#define PLUGIN_H

#include <QTextStream>
#include <QWidget>
#include <QIcon>

/**
 * @brief The Plugin class is an interface for all plugins.
 *
 */
class Plugin {

public:

    /**
     * @brief getName returns plugin name.
     *
     * @return name of plugin
     */
    virtual QString getName() = 0;

    /**
     * @brief getConfigurationWidget returns config widget of plugin.
     *
     * @return plugin configuration widget
     */
    virtual QSharedPointer<QWidget> getConfigurationWidget() = 0;

    /**
     * @brief saveConfiguration saves changes on config widget.
     *
     */
    virtual void saveConfiguration() = 0;

    /**
     * @brief getInputWidget returns input widget of plugin (optional).
     *
     * @return plugin input widget
     */
    virtual QSharedPointer<QWidget> getInputWidget() {
        return {};
    };


    /**
     * @brief getPluginIcon returns the Icon of the Plugin
     * @return the plugin Icon
     */
    virtual QSharedPointer<QIcon> getPluginIcon() = 0;

};


#endif //PLUGIN_H
