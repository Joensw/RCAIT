#include "classifiertrainer.h"

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
    return nullptr;
}

ClassificationResult *ClassifierTrainer::getLastClassificationResult()
{
    return nullptr;
}

bool ClassifierTrainer::getAugmentationPreview(QString pluginName, QString inputPath)
{
    return false;
}
