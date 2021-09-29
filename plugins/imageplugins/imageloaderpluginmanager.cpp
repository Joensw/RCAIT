/**
 * @file imageloaderpluginmanager.cpp
 *
 * @brief implements functions of class ImageLoaderPluginManager
 */
#include "imageloaderpluginmanager.h"

ImageLoaderPluginManager::ImageLoaderPluginManager() = default;

void ImageLoaderPluginManager::loadPlugins(QString pluginDir) {
    m_plugins.clear();
    m_pluginConfigurationWidgets.clear();
    m_pluginIcons.clear();

    QDir pluginsDir(pluginDir);
    for (const QString &fileName: pluginsDir.entryList(QDir::Files)) {
        if (!QLibrary::isLibrary(fileName)) continue;

        QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName));

        auto *imageLoaderPlugin = qobject_cast<ImageLoaderPlugin *>(pluginLoader.instance());
        if (imageLoaderPlugin) {
            imageLoaderPlugin->init();
            m_pluginConfigurationWidgets << imageLoaderPlugin->getConfigurationWidget();
            m_plugins[imageLoaderPlugin->getName()] = QSharedPointer<ImageLoaderPlugin>(imageLoaderPlugin);
            m_pluginIcons << imageLoaderPlugin->getPluginIcon();
        }
    }


}

QSharedPointer<QWidget> ImageLoaderPluginManager::getConfigurationWidget(QString pluginName) {
    if (!m_plugins.contains(pluginName)) {
        qWarning() << "No Image Loader Plugin with the name " << pluginName << " found!";
        return {new QWidget, &QObject::deleteLater};
    }
    return m_plugins[pluginName]->getConfigurationWidget();
}

void ImageLoaderPluginManager::saveConfiguration(QString pluginName) {
    if (m_plugins.contains(pluginName))
        m_plugins[pluginName]->saveConfiguration();
    else
        qWarning() << "No Image Loader Plugin with the name " << pluginName << " found!";

}

QSharedPointer<QWidget> ImageLoaderPluginManager::getInputWidget(QString pluginName) {
    if (m_plugins.contains(pluginName))
        return m_plugins[pluginName]->getConfigurationWidget();

    qWarning() << "No Image Loader Plugin with the name " << pluginName << " found!";
    return {new QWidget, &QObject::deleteLater};
}

bool ImageLoaderPluginManager::loadImages(const QString &path, ProgressablePlugin *receiver, const QString &pluginName,
                                          int count,
                                          const QStringList &labels) {
    if (m_plugins.contains(pluginName))
        return m_plugins[pluginName]->loadImages(path, receiver, count, labels);

    qWarning() << "No Image Loader Plugin with the name " << pluginName << " found!";
    return false;
}

QStringList ImageLoaderPluginManager::getNamesOfPlugins() {
    return m_plugins.keys();
}

QList<QSharedPointer<QWidget>> ImageLoaderPluginManager::getConfigurationWidgets() {
    return m_pluginConfigurationWidgets;
}

QList<QSharedPointer<QIcon>> ImageLoaderPluginManager::getPluginIcons()
{
    return m_pluginIcons;
}
