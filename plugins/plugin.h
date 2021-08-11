#ifndef PLUGIN_H
#define PLUGIN_H

#include <QTextStream>
#include <QWidget>

class Plugin {

public:
    virtual QString getName() = 0;
    virtual QWidget*  getConfigurationWidget() = 0;
    virtual void saveConfiguration() = 0;
    virtual QWidget*  getInputWidget() = 0;

};


#endif //PLUGIN_H
