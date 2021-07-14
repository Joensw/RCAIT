#ifndef RCAIT_PLUGIN_H
#define RCAIT_PLUGIN_H

#include <QTextStream>
#include <QWidget>

class Plugin {

public:
    virtual QString getName();
    virtual QWidget*  getConfigurationWidget();
    virtual void saveConfiguration();
    virtual QWidget*  getInputWidget();

};


#endif //RCAIT_PLUGIN_H
