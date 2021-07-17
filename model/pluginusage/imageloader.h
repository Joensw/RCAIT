#ifndef RCAIT_IMAGELOADER_H
#define RCAIT_IMAGELOADER_H


#include <QStringList>
#include "imagesearchthread.h"

class ImageLoader {
public:
    ImageLoader();
    void loadInputImages(int count, QStringList labels, QString pluginName, QString tempImageDir);

signals:
    void sig_imagesReady();
//TODO connect

private:
    ImageSearchThread* m_imageSearchThread;

};


#endif //RCAIT_IMAGELOADER_H
