#ifndef RCAIT_IMAGELOADERPLUGIN_H
#define RCAIT_IMAGELOADERPLUGIN_H

#include <QString>
#include <pluginusage/progressableplugin.h>
#include "plugin.h"

//Todo: Extend Plugin class
class ImageLoaderPlugin : public Plugin{
public:
    virtual bool loadImages(QString path, ProgressablePlugin* receiver, int count, QStringList labels) = 0;
};

QT_BEGIN_NAMESPACE

#define ImageLoaderPlugin_iid "de.Fraunhofer.IOSB.RCAIT.ImageLoaderPlugin"

Q_DECLARE_INTERFACE(ImageLoaderPlugin, ImageLoaderPlugin_iid)
QT_END_NAMESPACE

#endif //RCAIT_IMAGELOADERPLUGIN_H
