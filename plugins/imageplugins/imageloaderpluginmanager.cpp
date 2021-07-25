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
            imageLoaderPlugin->init(); //ToDo: call init function if necessary
            m_pluginConfigurationWidgets.append(imageLoaderPlugin->getConfigurationWidget());
            if (imageLoaderPlugin){

                m_pluginsSharedPointer.insert( imageLoaderPlugin->getName(), QSharedPointer<ImageLoaderPlugin>(imageLoaderPlugin));

            }
            //pluginLoader.unload(); //ToDo: Maybe use this
        }
    }


}

QWidget *ImageLoaderPluginManager::getConfigurationWidget(QString pluginName) {
    return m_pluginsSharedPointer.value(pluginName)->getConfigurationWidget();
}

void ImageLoaderPluginManager::saveConfiguration(QString pluginName) {
    m_pluginsSharedPointer.value(pluginName)->saveConfiguration();
}

QWidget *ImageLoaderPluginManager::getInputWidget(QString pluginName) {
    if(m_pluginsSharedPointer.isEmpty()) return new QWidget();
    return m_pluginsSharedPointer.value(pluginName)->getConfigurationWidget();
}

bool ImageLoaderPluginManager::loadImages(QString path, ProgressablePlugin *receiver, QString pluginName, int count,
                                          QStringList labels) {
   return m_pluginsSharedPointer.value(pluginName)->loadImages(path, receiver, count, labels);;
}

QStringList ImageLoaderPluginManager::getNamesOfPlugins()
{
    return m_pluginsSharedPointer.keys();
}

QList<QWidget *> ImageLoaderPluginManager::getConfigurationWidgets()
{
    return m_pluginConfigurationWidgets;
}
