#include "classificationpluginmanager.h"

#include <QPluginLoader>

ClassificationPluginManager::ClassificationPluginManager()
{

}

void ClassificationPluginManager::loadPlugins(QString pluginDir)
{
    m_plugins.clear();
    m_pluginConfigurationWidgets.clear();


    QDir pluginsDir(pluginDir);
    const QStringList entries = pluginsDir.entryList(QDir::Files);

    for (const QString &fileName : entries) {
        QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName));
        QObject *plugin = pluginLoader.instance();
        if (plugin) {
            ClassificationPlugin* classificationPlugin = qobject_cast<ClassificationPlugin *>(plugin);
            if (classificationPlugin){
                classificationPlugin->init();
                m_pluginConfigurationWidgets.append(classificationPlugin->getConfigurationWidget());
                m_plugins.insert( classificationPlugin->getName(), classificationPlugin);

            }
            //pluginLoader.unload(); //ToDo: Maybe use this
        }
    }


}


QWidget *ClassificationPluginManager::getConfigurationWidget(QString pluginName)
{
    return m_plugins.value(pluginName)->getConfigurationWidget();
}

void ClassificationPluginManager::saveConfiguration(QString pluginName)
{
    m_plugins.value(pluginName)->saveConfiguration();
}

QWidget *ClassificationPluginManager::getInputWidget(QString pluginName)
{
    if(m_plugins.isEmpty()) return new QWidget();
    return m_plugins.value(pluginName)->getDataAugmentationInputWidget();
}

QStringList ClassificationPluginManager::getModelNames(QString pluginName)
{
    return m_plugins.value(pluginName)->getAssociatedModels();
}

bool ClassificationPluginManager::createNewModel(QString modelName, QString pluginName, QString baseModel)
{
    return m_plugins.value(pluginName)->createNewModel(modelName,baseModel);
}

bool ClassificationPluginManager::getAugmentationPreview(QString pluginName, QString modelName, QString inputPath, QString targetPath, int amount)
{
    return m_plugins.value(pluginName)->getAugmentationPreview(modelName, inputPath, targetPath, amount);
}

bool ClassificationPluginManager::removeModel(QString modelName, QString pluginName)
{
    return m_plugins.value(pluginName)->removeModel(modelName);
}

TrainingResult *ClassificationPluginManager::train(QString pluginName, QString modelName, QString trainDatasetPath, QString validationDatasetPath, QString workingDirectory, ProgressablePlugin * receiver)
{
    return m_plugins.value(pluginName)->train(modelName, trainDatasetPath, validationDatasetPath, workingDirectory, receiver);
}

ClassificationResult *ClassificationPluginManager::classify(QString pluginName, QString inputImageDirPath, QString trainDatasetPath, QString workingDirectory, QString modelName, ProgressablePlugin * receiver)
{
    return m_plugins.value(pluginName)->classify(inputImageDirPath, trainDatasetPath, workingDirectory, modelName, receiver);
}

QList<QWidget *> ClassificationPluginManager::getConfigurationWidgets()
{
    return m_pluginConfigurationWidgets;
}

QStringList ClassificationPluginManager::getClassificationPluginBases(QString plugin)
{
    QStringList test = QStringList();
    test.append("base#1");
    test.append("base#2");
    return test;
}

QStringList ClassificationPluginManager::getNamesOfPlugins() {
    return m_plugins.keys();
}
