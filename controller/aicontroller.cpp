#include "aicontroller.h"


AIController::AIController(DataManager *dataManager, InputImagesWidget *inputImagesWidget, AITrainingWidget *aiTrainingTab)
{
    mDataManager = dataManager;
    mInputImagesWidget = inputImagesWidget;
    mAiTrainingWidget = aiTrainingTab;
    mTrainer = new Trainer;
    mClassifier = new Classifier;


    //connect augmentation preview
    //mAItrainingWIdget sig_showAugmentationPreview         AI Controller slot_showAugmentationPreview



    //connect progress
    connect(mClassifier, &Classifier::sig_progress, mInputImagesWidget, &InputImagesWidget::slot_progress);
    connect(mTrainer, &Trainer::sig_progress, mAiTrainingWidget, &AITrainingWidget::slot_progress);

    //connect classification parts
    connect(mInputImagesWidget, &InputImagesWidget::sig_startClassify, this, &AIController::slot_startClassify);
    connect(mInputImagesWidget, &InputImagesWidget::sig_abortClassify, this, &AIController::slot_abortClassify);
    connect(mClassifier, &Classifier::sig_classificationResultUpdated, this, &AIController::slot_classificationResultUpdated);
    connect(mClassifier, &Classifier::sig_progress, mInputImagesWidget, &InputImagesWidget::slot_progress);

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
    QString currentClassificationPlugin = mDataManager->getCurrentClassificationPlugin();
    QString projectDatasetTrainSubDir = mDataManager->getProjectDataSetTrainSubdir();
    QString currentModel =  mDataManager->getCurrentModel();

    mClassifier->classify(currentClassificationPlugin,
                              path,
                              projectDatasetTrainSubDir,
                             "In AICOntroller den String noch mit Funktion ersetzen", //mDataManager->get();  hier muss ein temporäres workdir hin)
                              currentModel);
    emit mClassifier->sig_startClassification();
}

void AIController::slot_abortClassify()
{

}

void AIController::slot_showAugmentationPreview()
{
//ToDo: Daria schreibt hier was passiert
    //call bool ClassificationPluginManager::getAugmentationPreview(QString pluginName, QString modelName, QString inputPath, QString targetPath, int amount)

}

void AIController::slot_modelLoaded()
{
    mAiTrainingWidget->setAIConfigWidget(mDataManager->getInputWidget());
    //mAiTrainingWidget->setDataAugWidget(mDataManager->getDataAugWidget)
}
