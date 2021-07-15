#ifndef RCAIT_PLUGINMANAGER_H
#define RCAIT_PLUGINMANAGER_H

#include <QTextStream>
#include <QWidget>

class PluginManager {

public:
    virtual QWidget* getConfigurationWidget(QString pluginName) = 0;
    virtual void loadPlugins(QString pluginDir) = 0;
    virtual QWidget* getInputWidget(QString pluginName) = 0;
    virtual QStringList getNamesOfPlugins() = 0;
    virtual void saveConfiguration(QString pluginName) = 0;

};


#endif //RCAIT_PLUGINMANAGER_H
