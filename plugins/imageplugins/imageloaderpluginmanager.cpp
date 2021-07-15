#include "imageloaderpluginmanager.h"

ImageLoaderPluginManager::ImageLoaderPluginManager() {

}

void ImageLoaderPluginManager::loadPlugins(QString pluginDir) {
    QDir pluginsDir(pluginDir);
    const QStringList entries = pluginsDir.entryList(QDir::Files);

    for (const QString &fileName : entries) {
        QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName));
        QObject *plugin = pluginLoader.instance();
        if (plugin) {
            ImageLoaderPlugin* imageLoaderPlugin = qobject_cast<ImageLoaderPlugin *>(plugin);
            //imageLoaderPlugin->init(); ToDo: call init function if necessary
            if (imageLoaderPlugin){
                m_plugins.insert(fileName,imageLoaderPlugin);
            }
            //pluginLoader.unload(); ToDo: Maybe use this
        }
    }


}

QWidget *ImageLoaderPluginManager::getConfigurationWidget(QString pluginName) {
    return m_plugins.value(pluginName)->getConfigurationWidget();
}

void ImageLoaderPluginManager::saveConfiguration(QString pluginName) {
    m_plugins.value(pluginName)->saveConfiguration();
}

QWidget *ImageLoaderPluginManager::getInputWidget(QString pluginName) {
    return m_plugins.value(pluginName)->getConfigurationWidget();
}

bool ImageLoaderPluginManager::loadImages(QString path, ProgressablePlugin *receiver, QString pluginName, int count,
                                          QStringList labels) {
    return m_plugins.value(pluginName)->loadImages(path, *receiver, count, labels);;
}

QStringList ImageLoaderPluginManager::getNamesOfPlugins()
{
    return m_plugins.keys();
}
