#include "classificationpluginmanager.h"

ClassificationPluginManager::ClassificationPluginManager()
{

}

void ClassificationPluginManager::loadPlugins(QString pluginDir)
{

}

ClassificationPluginManager *ClassificationPluginManager::getInstance()
{

}

QWidget *ClassificationPluginManager::getConfigurationWidget(QString pluginName)
{

}

void ClassificationPluginManager::saveConfiguration(QString pluginName)
{

}

QWidget *ClassificationPluginManager::getInputWidget(QString pluginName)
{

}

QMap<QString, QString> ClassificationPluginManager::getModelNames(QString projectPath)
{

}

bool ClassificationPluginManager::createNewModel(QString ModelName, QString pluingName, QString baseModel)
{

}

bool ClassificationPluginManager::getAugmentationPreview(QString pluginName, QString inputPath)
{

}

bool ClassificationPluginManager::removeModel(QString modelName, QString pluginName)
{

}

TrainingResult *ClassificationPluginManager::train(QString pluginName, QString modelName, QString dataSetPath, ProgressablePlugin *receiver)
{

}

ClassificationResult *ClassificationPluginManager::classify(QString pluginName, QString inputImagePath, QString modelName, ProgressablePlugin *receiver)
{

}
