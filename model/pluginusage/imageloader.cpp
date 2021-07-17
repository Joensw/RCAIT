#include "model/pluginusage/imageloader.h"

ImageLoader::ImageLoader()
{

}

void ImageLoader::loadInputImages(int count, QStringList labels, QString pluginName, QString tempImageDir)
{
     m_imageSearchThread = new ImageSearchThread((ProgressablePlugin*) this, tempImageDir,pluginName,count, labels);
     m_imageSearchThread->start();
}

