#include "imageloaderpluginmock.h"




bool ImageLoaderPluginMock::loadImages(QString path, ProgressablePlugin *receiver, int imageCount, QStringList label)
{
    return true;
}

QWidget *ImageLoaderPluginMock::getConfigurationWidget()
{
    return nullptr;
}

void ImageLoaderPluginMock::saveConfiguration()
{

}

void ImageLoaderPluginMock::init()
{

}

QString ImageLoaderPluginMock::getName()
{
    return PLUGIN_NAME;
}

QWidget *ImageLoaderPluginMock::getInputWidget()
{
    return nullptr;
}

void ImageLoaderPluginMock::slot_abort()
{

}

void ImageLoaderPluginMock::slot_readOutPut()
{

}

void ImageLoaderPluginMock::slot_pluginFinished()
{

}