#include "aicontroller.h"


AIController::AIController(QString *dataManager, InputImagesWidget *inputImagesWidget, QString *aiTrainingTab, ClassifierTrainer *classifierTrainer)
{
    this->dataManager = dataManager;
    this->inputImagesWidget = inputImagesWidget;
    this->aiTrainingTab = aiTrainingTab;
    this->classifierTrainer = classifierTrainer;

}

void AIController::slot_startTraining()
{

}

void AIController::slot_abortTraining()
{

}

void AIController::slot_results()
{

}

void AIController::slot_trainingResultUpdated()
{

}

void AIController::slot_classificationResultUpdated()
{

}

void AIController::slot_startClassify(QString path)
{
    this->trainingPath = path;
    classify();
}

void AIController::slot_abortClassify()
{

}

void AIController::slot_showAugmentationPreview()
{

}

void AIController::train()
{

}

void AIController::classify()
{

}
