#include "mmclassificationplugin.h"


MMClassificationPlugin::MMClassificationPlugin()
{
    pluginSettings = new MMClassificationSettings();
}

MMClassificationPlugin::~MMClassificationPlugin()
{

}

QString MMClassificationPlugin::getName()
{
    return m_name;
}

QWidget* MMClassificationPlugin::getConfigurationWidget()
{
    return pluginSettings;
}

void MMClassificationPlugin::saveConfiguration()
{
    qobject_cast<MMClassificationSettings *>(pluginSettings)->saveSettings();
}

QWidget* MMClassificationPlugin::getInputWidget()
{
    return inputOptions;
}

QStringList MMClassificationPlugin::getAssociatedModels()
{

}

bool MMClassificationPlugin::createNewModel(QString modelName, QString baseModel)
{

}

bool MMClassificationPlugin::removeModel(QString modelName)
{

}

bool MMClassificationPlugin::getAugmentationPreview(QString modelName, QString inputPath, QString targetPath, int amount)
{

}

TrainingResult* MMClassificationPlugin::train(QString modelName, QString trainDatasetPath, QString validationDatasetPath, QString workingDirectory, ProgressablePlugin *receiver)
{

}

ClassificationResult* MMClassificationPlugin::classify(QString inputImageDirPath,QString trainDatasetPath, QString workingDirPath, QString modelName, ProgressablePlugin *receiver)
{

}

QWidget* MMClassificationPlugin::getDataAugmentationInputWidget()
{
    return dataAugmentationInput;
}

void MMClassificationPlugin::slot_readOutPut()
{

}

void MMClassificationPlugin::slot_pluginFinished()
{

}
