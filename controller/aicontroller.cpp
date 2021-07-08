#include "aicontroller.h"


AIController::AIController(DataManager *dataManager, InputImagesWidget *inputImagesWidget, AITrainingWidget *aiTrainingTab)
{
    mDataManager = dataManager;
    mInputImagesWidget = inputImagesWidget;
    mAiTrainingWidget = aiTrainingTab;
    mClassifierTrainer = new ClassifierTrainer;

    //connect progress
    connect(mClassifierTrainer, &ClassifierTrainer::sig_progress, mInputImagesWidget, &InputImagesWidget::slot_progress);

    //connect classification parts
    connect(mInputImagesWidget, &InputImagesWidget::sig_startClassify, this, &AIController::slot_startClassify);
    connect(mInputImagesWidget, &InputImagesWidget::sig_abortClassify, this, &AIController::slot_abortClassify);
    connect(mClassifierTrainer, &ClassifierTrainer::sig_classificationResultUpdated, this, &AIController::slot_classificationResultUpdated);

    //connect training parts



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
    mTrainingPath = path;
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
