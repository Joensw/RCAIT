#include "mmclassificationplugin.h"


MMClassificationPlugin::MMClassificationPlugin()
{

}

MMClassificationPlugin::~MMClassificationPlugin()
{

}

QString MMClassificationPlugin::getName()
{

}

QWidget* MMClassificationPlugin::getConfigurationWidget()
{

}

void MMClassificationPlugin::saveConfiguration()
{

}

QWidget* MMClassificationPlugin::getInputWidget()
{

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

void MMClassificationPlugin::slot_readOutPut()
{

}

void MMClassificationPlugin::slot_pluginFinished()
{

}
