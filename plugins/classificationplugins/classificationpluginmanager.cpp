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
        QObject *plugin = pluginLoader.instance();
        if (plugin) {
            ClassificationPlugin *classificationPlugin = qobject_cast<ClassificationPlugin *>(plugin);
            if (classificationPlugin) {
                classificationPlugin->init();
                m_pluginConfigurationWidgets.append(classificationPlugin->getConfigurationWidget());
                m_plugins.insert(classificationPlugin->getName(), classificationPlugin);

            }
            //pluginLoader.unload(); //ToDo: Maybe use this
        }
    }
}


QWidget *ClassificationPluginManager::getConfigurationWidget(QString pluginName) {
    if (!m_plugins.contains(pluginName)) {
        qWarning() << "No Classification Plugin with the name " << pluginName << " found!";
        return new QWidget();
    }
    return m_plugins.value(pluginName)->getConfigurationWidget();
}

void ClassificationPluginManager::saveConfiguration(QString pluginName) {
    if (!m_plugins.contains(pluginName)) {
        qWarning() << "No Classification Plugin with the name " << pluginName << " found!";
        return;
    }
    m_plugins.value(pluginName)->saveConfiguration();
}

QWidget *ClassificationPluginManager::getInputWidget(QString pluginName) {
    if (!m_plugins.contains(pluginName)) {
        qWarning() << "No Classification Plugin with the name " << pluginName << " found!";
        return new QWidget();
    }
    return m_plugins.value(pluginName)->getInputWidget();
}

QWidget *ClassificationPluginManager::getDataAugmentationInputWidget(const QString &pluginName) {
    if (!m_plugins.contains(pluginName)) {
        qWarning() << "No Classification Plugin with the name " << pluginName << " found!";
        return new QWidget();
    }
    return m_plugins.value(pluginName)->getDataAugmentationInputWidget();
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
ClassificationPluginManager::getAugmentationPreview(const QString &pluginName, QString modelName, QString inputPath,
                                                    QString targetPath, int amount) {
    if (!m_plugins.contains(pluginName)) {
        qWarning() << "No Classification Plugin with the name " << pluginName << " found!";
        return false;
    }
    return m_plugins.value(pluginName)->getAugmentationPreview(std::move(modelName), std::move(inputPath),
                                                               std::move(targetPath), amount);
}

bool ClassificationPluginManager::removeModel(QString modelName, const QString &pluginName) {
    if (!m_plugins.contains(pluginName)) {
        qWarning() << "No Classification Plugin with the name " << pluginName << " found!";
        return false;
    }
    return m_plugins.value(pluginName)->removeModel(std::move(modelName));
}

TrainingResult *
ClassificationPluginManager::train(const QString &pluginName, QString modelName, QString trainDatasetPath,
                                   QString validationDatasetPath, QString workingDirectory,
                                   ProgressablePlugin *receiver) {
    if (!m_plugins.contains(pluginName)) {
        qWarning() << "No Classification Plugin with the name " << pluginName << " found!";
        return new TrainingResult({}, {}, {}, {}, 0, 0);
    }
    return m_plugins.value(pluginName)->train(std::move(modelName), std::move(trainDatasetPath),
                                              std::move(validationDatasetPath), std::move(workingDirectory),
                                              receiver);
}

ClassificationResult *
ClassificationPluginManager::classify(const QString &pluginName, QString inputImageDirPath, QString trainDatasetPath,
                                      QString workingDirectory, QString modelName, ProgressablePlugin *receiver) {
    if (!m_plugins.contains(pluginName)) {
        qWarning() << "No Classification Plugin with the name " << pluginName << " found!";
        return new ClassificationResult({}, {}, {});
    }
    return m_plugins.value(pluginName)->classify(std::move(inputImageDirPath), std::move(trainDatasetPath),
                                                 std::move(workingDirectory), std::move(modelName),
                                                 receiver);
}

QList<QWidget *> ClassificationPluginManager::getConfigurationWidgets() {
    return m_pluginConfigurationWidgets;
}

QStringList ClassificationPluginManager::getClassificationPluginBases(const QString &pluginName) {
    if (!m_plugins.contains(pluginName)) {
        qWarning() << "No Classification Plugin with the name " << pluginName << " found!";
        return {};
    }
    return m_plugins.value(pluginName)->getAssociatedModels();
}

QStringList ClassificationPluginManager::getNamesOfPlugins() {
    return m_plugins.keys();
}
