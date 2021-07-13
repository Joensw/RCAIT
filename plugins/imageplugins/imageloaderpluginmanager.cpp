#include "imageloaderpluginmanager.h"

ImageLoaderPluginManager::ImageLoaderPluginManager() {

}

void ImageLoaderPluginManager::loadPlugins(QString pluginDir) {

}

QWidget *ImageLoaderPluginManager::getConfigurationWidget(QString pluginName) {
    return nullptr;
}

void ImageLoaderPluginManager::saveConfiguration(QString pluginName) {

}

QWidget *ImageLoaderPluginManager::getInputWidget(QString pluginName) {
    return nullptr;
}

bool ImageLoaderPluginManager::loadImages(QString path, ProgressablePlugin *receiver, QString pluginName, int count,
                                          QStringList labels) {
    return false;
}
