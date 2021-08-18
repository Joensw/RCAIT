#include "aicontroller.h"


AIController::AIController(DataManager *dataManager, InputImagesWidget *inputImagesWidget, AITrainingWidget *aiTrainingTab)
{
    mDataManager = dataManager;
    mInputImagesWidget = inputImagesWidget;
    mAiTrainingWidget = aiTrainingTab;
    mTrainer = new Trainer;
    mClassifier = new Classifier;

    //connect progress
    connect(mClassifier, &Classifier::sig_progress, mInputImagesWidget, &InputImagesWidget::slot_progress);

    //connect classification parts
    connect(mInputImagesWidget, &InputImagesWidget::sig_startClassify, this, &AIController::slot_startClassify);
    connect(mInputImagesWidget, &InputImagesWidget::sig_abortClassify, this, &AIController::slot_abortClassify);
    connect(mClassifier, &Classifier::sig_classificationResultUpdated, this, &AIController::slot_classificationResultUpdated);

    //connect training parts
    connect(mAiTrainingWidget, &AITrainingWidget::sig_startTraining, this, &AIController::slot_startTraining);
    connect(mAiTrainingWidget, &AITrainingWidget::sig_abortTraining, this, &AIController::slot_abortTraining);
    connect(mTrainer, &Trainer::sig_trainingResultUpdated, this, &AIController::slot_trainingResultUpdated);

}

void AIController::slot_startTraining()
{  
   mTrainer->train( mDataManager->getCurrentClassificationPlugin(),
                              mDataManager->getCurrentModel(),
                              mDataManager->getProjectDataSetTrainSubdir(),
                              mDataManager->getProjectDataSetValSubdir(),
                              NULL); //mDataManager->get();  hier muss ein temporäres workdir hin)
   emit mTrainer->sig_startTraining();

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
    mClassifier->classify(mDataManager->getCurrentClassificationPlugin(),
                               path,
                               mDataManager->getProjectDataSetTrainSubdir(),
                               NULL, //mDataManager->get();  hier muss ein temporäres workdir hin)
                               mDataManager->getCurrentModel());
    emit mClassifier->sig_startClassification();
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
    //mClassifierTrainer->classify(mDataManager->getCurrentClassificationPlugin(), mDataManager->getCurrentModel(), mClassificationPath);
}
