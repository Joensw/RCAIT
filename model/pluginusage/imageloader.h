#ifndef IMAGELOADER_H
#define IMAGELOADER_H

#include "model/pluginusage/progressableplugin.h"

class ImageLoader : public ProgressablePlugin
{
public:
    ImageLoader();
    void loadInputImages(int count, QStringList labels, QString pluginName, QString tempImageDir);

signals:
    void sig_imagesReady();
};

#endif // IMAGELOADER_H
