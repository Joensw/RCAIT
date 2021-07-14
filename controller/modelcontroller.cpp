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
    //QStringList pluginNames = mDataManager->getClassificationPluginNames();
    //mNewModelDialog = new NewModelDialog(nullptr, pluginNames);
    //für test zwecke eigentlicher code Steht obendrüber
    QStringList pluginNames = QStringList();
    pluginNames.append("MMClassification");
    pluginNames.append("TensorFlow");
    pluginNames.append("Plugin#3");
    mNewModelDialog = new NewModelDialog(nullptr, pluginNames);

    mNewModelDialog->setAttribute(Qt::WA_DeleteOnClose, true);
    connect(mNewModelDialog, &NewModelDialog::sig_newModelConfirm, this, &ModelController::slot_newModelConfirm);
    connect(mNewModelDialog, &NewModelDialog::sig_pluginSelected, this, &ModelController::slot_pluginSelected);
    mNewModelDialog->show();
}

void ModelController::slot_newModelConfirm(QString modelName, QString pluginName, QString baseModel)
{
    mDataManager->createNewModel(modelName, pluginName, baseModel);
    mNewModelDialog->close();
}

void ModelController::slot_removeModel(QString modelName)
{
    mRemoveModelDialog = new RemoveModelDialog(nullptr, modelName);
    mRemoveModelDialog->setAttribute(Qt::WA_DeleteOnClose, true);
    connect(mRemoveModelDialog, &RemoveModelDialog::sig_removeModelConfirm, this, &ModelController::slot_removeModelConfirm);
    mRemoveModelDialog->show();
}

void ModelController::slot_removeModelConfirm()
{
    QString name = mRemoveModelDialog->getModelName();
    mDataManager->removeModel(name, "PLACEHOLDER");
    mRemoveModelDialog->close();
}

void ModelController::slot_loadModel(QString modelName)
{
    mDataManager->loadModel(modelName, "PLACEHOLDER");

}

void ModelController::slot_pluginSelected(QString pluginName)
{
    //get the bases for this plugin and give them to the dialog
}