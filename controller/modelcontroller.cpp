#include "modelcontroller.h"



ModelController::ModelController(QObject *parent, DataManager *dataManager, ImportFilesWidget *importFilesWidget)
{
    this->mDataManager = dataManager;
    this->mImportFilesWidget = importFilesWidget;
    connect(mImportFilesWidget, &ImportFilesWidget::sig_newModel, this, &ModelController::slot_newModel);
    connect(mImportFilesWidget, &ImportFilesWidget::sig_removeModel, this, &ModelController::slot_removeModel);
    connect(mImportFilesWidget, &ImportFilesWidget::sig_loadModel, this, &ModelController::slot_loadModel);
}

void ModelController::slot_newModel()
{
    QStringList pluginNames = mDataManager->getClassificationPluginNames();
    mNewModelDialog = new NewModelDialog(nullptr, pluginNames);

    mNewModelDialog->setAttribute(Qt::WA_DeleteOnClose, true);
    mNewModelDialog->setModal(true);
    connect(mNewModelDialog, &NewModelDialog::sig_newModelConfirm, this, &ModelController::slot_newModelConfirm);
    connect(mNewModelDialog, &NewModelDialog::sig_pluginSelected, this, &ModelController::slot_pluginSelected);
    mNewModelDialog->show();
}

void ModelController::slot_newModelConfirm(QString modelName, QString pluginName, QString baseModel)
{
    mDataManager->createNewModel(modelName, pluginName, baseModel);
    mImportFilesWidget->addNewModel(modelName);
    mNewModelDialog->close();
}

void ModelController::slot_removeModel(QString modelName)
{
    mRemoveModelDialog = new RemoveModelDialog(nullptr, modelName);
    mRemoveModelDialog->setAttribute(Qt::WA_DeleteOnClose, true);
    mRemoveModelDialog->setModal(true);
    connect(mRemoveModelDialog, &RemoveModelDialog::sig_removeModelConfirm, this, &ModelController::slot_removeModelConfirm);
    mRemoveModelDialog->show();
}

void ModelController::slot_removeModelConfirm()
{
    QString modelName = mRemoveModelDialog->getModelName();
    mDataManager->removeModel(modelName);
    mImportFilesWidget->clearModelList();
    mImportFilesWidget->addModels(mDataManager->getModelNamesOfCurrentProject());
    mRemoveModelDialog->close();
}

void ModelController::slot_loadModel(QString modelName)
{
    mDataManager->loadModel(modelName, "PLACEHOLDER");
    emit sig_modelLoaded();
}

void ModelController::slot_pluginSelected(QString pluginName)
{
    //get bases of the plugin with that name and set the second dropdown in the dialog
    QStringList test = mDataManager->getPluginBases(pluginName);
    mNewModelDialog->setAvailableBases(test);

}
