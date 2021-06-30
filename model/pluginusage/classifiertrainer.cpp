#include "model/pluginusage/classifiertrainer.h"

ClassifierTrainer::ClassifierTrainer()
{

}

void ClassifierTrainer::train(QString pluginName, QString modelName, QString imagePath)
{

}

void ClassifierTrainer::classify(QString pluginName, QString modelName, QString imagePath)
{

}

TrainingResult *ClassifierTrainer::getLastTrainingResult()
{
    return NULL;
}

ClassificationResult *ClassifierTrainer::getLastClassificationResult()
{
    return NULL;
}

bool ClassifierTrainer::getAugmentationPreview(QString pluginName, QString inputPath)
{
    return false;
}
