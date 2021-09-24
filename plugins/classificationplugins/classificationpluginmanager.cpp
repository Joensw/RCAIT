#include "classificationpluginmanager.h"

#include <QPluginLoader>
#include <utility>

ClassificationPluginManager::ClassificationPluginManager() = default;

void ClassificationPluginManager::loadPlugins(QString pluginDir) {
    m_plugins.clear();
    m_pluginConfigurationWidgets.clear();

    QDir pluginsDir(pluginDir);
    const QStringList entries = pluginsDir.entryList(QDir::Files);

    for (const QString &fileName: entries) {
        if (!QLibrary::isLibrary(fileName)) continue;
        QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName));

        auto *classificationPlugin = qobject_cast<ClassificationPlugin *>(pluginLoader.instance());
        if (classificationPlugin) {
            classificationPlugin->init();
            m_pluginConfigurationWidgets << classificationPlugin->getConfigurationWidget();
            m_plugins[classificationPlugin->getName()] = classificationPlugin;
        }
    }
}


QSharedPointer<QWidget> ClassificationPluginManager::getConfigurationWidget(QString pluginName) {
    if (m_plugins.contains(pluginName))
        return m_plugins[pluginName]->getConfigurationWidget();

    qWarning() << "No Classification Plugin with the name " << pluginName << " found!";
    return {new QWidget, &QObject::deleteLater};
}

void ClassificationPluginManager::saveConfiguration(QString pluginName) {
    if (m_plugins.contains(pluginName))
        m_plugins[pluginName]->saveConfiguration();
    else
        qWarning() << "No Classification Plugin with the name " << pluginName << " found!";
}

QSharedPointer<QWidget> ClassificationPluginManager::getInputWidget(QString pluginName) {
    if (m_plugins.contains(pluginName))
        return m_plugins[pluginName]->getInputWidget();

    qWarning() << "No Classification Plugin with the name " << pluginName << " found!";
    return {new QWidget(), &QObject::deleteLater};
}

QSharedPointer<QWidget> ClassificationPluginManager::getDataAugmentationInputWidget(const QString &pluginName) {
    if (m_plugins.contains(pluginName))
        return m_plugins[pluginName]->getDataAugmentationInputWidget();

    qWarning() << "No Classification Plugin with the name " << pluginName << " found!";
    return {new QWidget, &QObject::deleteLater};
}

QStringList ClassificationPluginManager::getModelNames(const QString &pluginName) {
    // return m_plugins.value(pluginName)->getAssociatedModels();
    // the user created models to show depends on the chosen project and not on the chosen classification plugin
    // but user created models known to the main application must be removed,
    // if the plugin containing its corresponding base models isn't present
    // this task will be implemented in the model manager
    //TODO Fill
    return {};
}

bool ClassificationPluginManager::createNewModel(QString modelName, const QString &pluginName, QString baseModel) {
    if (!m_plugins.contains(pluginName)) {
        qWarning() << "No Classification Plugin with the name " << pluginName << " found!";
        return false;
    }
    return m_plugins.value(pluginName)->createNewModel(std::move(modelName), std::move(baseModel));
}

bool
ClassificationPluginManager::getAugmentationPreview(const QString &pluginName, const QString &modelName,
                                                    const QString &inputPath,
                                                    const QString &targetPath, int amount) {
    if (!m_plugins.contains(pluginName)) {
        qWarning() << "No Classification Plugin with the name " << pluginName << " found!";
        return false;
    }
    return m_plugins.value(pluginName)->getAugmentationPreview(modelName, inputPath,
                                                               targetPath, amount);
}

bool ClassificationPluginManager::removeModel(QString modelName, const QString &pluginName) {
    if (!m_plugins.contains(pluginName)) {
        qWarning() << "No Classification Plugin with the name " << pluginName << " found!";
        return false;
    }
    return m_plugins.value(pluginName)->removeModel(std::move(modelName));
}

TrainingResult *
ClassificationPluginManager::train(const QString &pluginName, const QString &modelName, QString trainDatasetPath,
                                   QString validationDatasetPath, QString workingDirectory,
                                   ProgressablePlugin *receiver) {
    if (!m_plugins.contains(pluginName)) {
        qWarning() << "No Classification Plugin with the name " << pluginName << " found!";
        return new TrainingResult(workingDirectory, {}, {}, {}, {}, 0, 0);
    }
    return m_plugins.value(pluginName)->train(modelName, std::move(trainDatasetPath),
                                              std::move(validationDatasetPath), std::move(workingDirectory),
                                              receiver);
}

ClassificationResult *
ClassificationPluginManager::classify(const QString &pluginName, const QString &inputImageDirPath,
                                      const QString &trainDatasetPath,
                                      const QString &workingDirectory, const QString &modelName,
                                      ProgressablePlugin *receiver) {
    if (!m_plugins.contains(pluginName)) {
        qWarning() << "No Classification Plugin with the name " << pluginName << " found!";
        return new ClassificationResult({}, {}, {});
    }
    return m_plugins[pluginName]->classify(inputImageDirPath, trainDatasetPath,
                                           workingDirectory, modelName,
                                           receiver);
}

QList<QSharedPointer<QWidget>> ClassificationPluginManager::getConfigurationWidgets() {
    return m_pluginConfigurationWidgets;
}

QStringList ClassificationPluginManager::getClassificationPluginBases(const QString &pluginName) {
    if (m_plugins.contains(pluginName))
        return m_plugins[pluginName]->getAssociatedModels();

    qWarning() << "No Classification Plugin with the name " << pluginName << " found!";
    return {};
}

QStringList ClassificationPluginManager::getNamesOfPlugins() {
    return m_plugins.keys();
}
