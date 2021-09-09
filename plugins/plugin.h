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
    virtual QWidget*  getConfigurationWidget() = 0;

    /**
     * @brief saveConfiguration saves changes on config widget.
     *
     */
    virtual void saveConfiguration() = 0;

    /**
     * @brief getInputWidget returns input widget of plugin.
     *
     * @return plugin input widget
     */
    virtual QWidget*  getInputWidget() = 0;

};


#endif //PLUGIN_H
