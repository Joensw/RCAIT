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

QWidget *MMClassificationPlugin::getConfigurationWidget()
{

}

void MMClassificationPlugin::saveConfiguration()
{

}

QWidget *MMClassificationPlugin::getInputWidget()
{

}

QStringList MMClassificationPlugin::getAssociatedModels(QString dataSet)
{

}

bool MMClassificationPlugin::createNewModel(QString modelName, QString baseModel)
{

}

bool MMClassificationPlugin::getAugmentationPreview(QString inputPath)
{

}

bool MMClassificationPlugin::removeModel(QString modelName)
{

}

TrainingResult *MMClassificationPlugin::train(QString modelName, QString dataSetPath, ProgressablePlugin *receiver)
{

}

ClassificationResult *MMClassificationPlugin::classify(QString inputImagePath, QString modelName, ProgressablePlugin *receiver)
{

}

void MMClassificationPlugin::slot_readOutPut()
{

}

void MMClassificationPlugin::slot_pluginFinished()
{

}
