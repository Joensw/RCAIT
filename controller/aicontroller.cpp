#include "aicontroller.h"
#include "imagegallery.h"
#include <QMessageBox>


AIController::AIController(DataManager *dataManager, InputImagesWidget *inputImagesWidget, AITrainingWidget *aiTrainingTab)
{
    mDataManager = dataManager;
    mInputImagesWidget = inputImagesWidget;
    mAiTrainingWidget = aiTrainingTab;
    mTrainer = new Trainer;
    mClassifier = new Classifier;


    //connect augmentation preview
    //mAItrainingWIdget sig_showAugmentationPreview
    connect(mAiTrainingWidget, &AITrainingWidget::sig_showAugmentationPreview, this, &AIController::slot_showAugmentationPreview);



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
   QString modelName = mDataManager->getCurrentModel();
   mTrainer->train( mDataManager->getCurrentClassificationPlugin(),
                              modelName,
                              mDataManager->getProjectDataSetTrainSubdir(),
                              mDataManager->getProjectDataSetValSubdir(),
                              mDataManager->createNewWorkSubDir(modelName)); //mDataManager->get();  hier muss ein temporäres workdir hin)
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
    QString projectName = mDataManager->getProjectName();
    QString modelName = mDataManager->getCurrentModel();
    QString lastWorkingDirectory = mTrainer->getRecentWorkingDir();
    mDataManager->saveLastWorkingDirectoryOfModel(projectName, modelName, lastWorkingDirectory);
}

void AIController::slot_classificationResultUpdated()
{

}

void AIController::slot_startClassify(QString path)
{
    QString currentClassificationPlugin = mDataManager->getCurrentClassificationPlugin();
    QString projectDatasetTrainSubDir = mDataManager->getProjectDataSetTrainSubdir();
    QString currentModel =  mDataManager->getCurrentModel();
    QString lastWorkingDirectory = mDataManager->recallLastWorkingDirectoryOfModel(mDataManager->getProjectName(), currentModel);

    mClassifier->classify(currentClassificationPlugin,
                              path,
                              projectDatasetTrainSubDir,
                              lastWorkingDirectory,
                              currentModel);
    emit mClassifier->sig_startClassification();
}

void AIController::slot_abortClassify()
{

}

void AIController::slot_showAugmentationPreview(int amount)
{
    QString pluginName = mDataManager->getCurrentClassificationPlugin();
    QString modelName = mDataManager->getCurrentModel();
    QString inputPath = mDataManager->getProjectDataSetTrainSubdir();
    QString targetPath = mDataManager->getProjectAugTempDir();
    //TODO: if no model was chosen it crashs
    if (!ClassificationPluginManager::getInstance().getAugmentationPreview(pluginName, modelName, inputPath, targetPath, amount)) {
        qDebug()<<"can not show preview";
        return;
    }
    mAiTrainingWidget->showImages(targetPath);
}

void AIController::slot_modelLoaded()
{
    mAiTrainingWidget->setAIConfigWidget(mDataManager->getInputWidget());
    mAiTrainingWidget->setDataAugWidget(mDataManager->getDataAugmentationInputWidget());
}
