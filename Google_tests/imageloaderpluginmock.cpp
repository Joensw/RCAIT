#include "imageloaderpluginmock.h"




bool ImageLoaderPluginMock::loadImages(const QString &path, ProgressablePlugin *receiver, int imageCount, const QStringList &label)
{
    return true;
}

QSharedPointer<QWidget> ImageLoaderPluginMock::getConfigurationWidget() {
    return pluginSettings;
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

QSharedPointer<QWidget> ImageLoaderPluginMock::getInputWidget() {
    return inputWidget;
}

QSharedPointer<QIcon> ImageLoaderPluginMock::getPluginIcon()
{
    return QSharedPointer<QIcon>(new QIcon());
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
