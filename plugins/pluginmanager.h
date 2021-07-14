#ifndef RCAIT_PLUGINMANAGER_H
#define RCAIT_PLUGINMANAGER_H

#include <QTextStream>
#include <QWidget>

class PluginManager {

public:
    virtual QWidget* getConfigurationWidget(QString pluginName);
    virtual void loadPlugins(QString pluginDir);
    virtual QWidget* getInputWidget(QString pluginName);
    virtual QStringList getNamesOfPlugins();
    virtual void saveConfiguration(QString pluginName);

};


#endif //RCAIT_PLUGINMANAGER_H
