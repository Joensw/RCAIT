#ifndef RCAIT_IMAGELOADERPLUGIN_H
#define RCAIT_IMAGELOADERPLUGIN_H

#include <QString>
#include <pluginusage/progressableplugin.h>
#include "Plugin.h"

//Todo: Extend Plugin class
class ImageLoaderPlugin : public Plugin{
public:
    virtual bool loadImages(QString path, ProgressablePlugin* receiver, QString pluginName, int count, QStringList labels);
};


#endif //RCAIT_IMAGELOADERPLUGIN_H
