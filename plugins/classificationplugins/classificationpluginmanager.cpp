#include "classificationpluginmanager.h"

ClassificationPluginManager::ClassificationPluginManager()
{

}

void ClassificationPluginManager::loadPlugins(QString pluginDir)
{

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
    return m_plugins.value(pluginName)->getConfigurationWidget();
}

QMap<QString, QString> ClassificationPluginManager::getModelNames(QString projectPath)
{

}

bool ClassificationPluginManager::createNewModel(QString modelName, QString pluginName, QString baseModel)
{
    return m_plugins.value(pluginName)->createNewModel(modelName,baseModel);
}

bool ClassificationPluginManager::getAugmentationPreview(QString pluginName, QString inputPath)
{
    return m_plugins.value(pluginName)->getAugmentationPreview(inputPath);
}

bool ClassificationPluginManager::removeModel(QString modelName, QString pluginName)
{
    return m_plugins.value(pluginName)->removeModel(modelName);
}

TrainingResult *ClassificationPluginManager::train(QString pluginName, QString modelName, QString dataSetPath, ProgressablePlugin *receiver)
{
    return m_plugins.value(pluginName)->train(modelName, dataSetPath, receiver);
}

ClassificationResult *ClassificationPluginManager::classify(QString pluginName, QString inputImagePath, QString modelName, ProgressablePlugin *receiver)
{
    return m_plugins.value(pluginName)->classify(inputImagePath, modelName, receiver);
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
