/**
 * @file modelcontroller.cpp
 *
 * @brief connects the logic of the model management with the user interface
 *
 * @author Andreas Ott
 */
#include "modelcontroller.h"

ModelController::ModelController(QObject *parent, DataManager *dataManager, ImportFilesWidget *importFilesWidget)
        : QObject(parent),
          mDataManager(dataManager),
          mImportFilesWidget(importFilesWidget) {

    connect(mImportFilesWidget, &ImportFilesWidget::sig_newModel, this, &ModelController::slot_newModel);
    connect(mImportFilesWidget, &ImportFilesWidget::sig_removeModel, this, &ModelController::slot_removeModel);
    connect(mImportFilesWidget, &ImportFilesWidget::sig_loadModel, this, &ModelController::slot_loadModel);
}

void ModelController::slot_newModel() {
    auto pluginNames = mDataManager->getClassificationPluginNames();
    mNewModelDialog = new NewModelDialog(nullptr, pluginNames);

    mNewModelDialog->setAttribute(Qt::WA_DeleteOnClose, true);
    mNewModelDialog->setModal(true);
    connect(mNewModelDialog, &NewModelDialog::sig_newModelConfirm, this, &ModelController::slot_newModelConfirm);
    connect(mNewModelDialog, &NewModelDialog::sig_pluginSelected, this, &ModelController::slot_pluginSelected);

    slot_pluginSelected(mNewModelDialog->getCurrentSelectedPlugin());

    mNewModelDialog->show();
}

void
ModelController::slot_newModelConfirm(const QString &modelName, const QString &pluginName, const QString &baseModel) {
    mDataManager->createNewModel(modelName, pluginName, baseModel);
    mImportFilesWidget->addNewModel(modelName);
    mNewModelDialog->close();
}

void ModelController::slot_removeModel(const QString &modelName) {
    mRemoveModelDialog = new RemoveModelDialog(nullptr, modelName);
    mRemoveModelDialog->setAttribute(Qt::WA_DeleteOnClose, true);
    mRemoveModelDialog->setModal(true);
    connect(mRemoveModelDialog, &RemoveModelDialog::sig_removeModelConfirm, this,
            &ModelController::slot_removeModelConfirm);
    mRemoveModelDialog->show();
}

void ModelController::slot_removeModelConfirm() {
    auto modelName = mRemoveModelDialog->getModelName();
    mDataManager->removeModel(modelName);
    mImportFilesWidget->clearModelList();
    mImportFilesWidget->addModels(mDataManager->getModelNamesOfCurrentProject());
    mRemoveModelDialog->close();
}

void ModelController::slot_loadModel(const QString &modelName) {
    auto projectName = mDataManager->getProjectName();
    auto pluginName = mDataManager->recallPluginNameOfModell(projectName, modelName);
    mDataManager->loadModel(modelName, pluginName);
    emit sig_modelLoaded();
}

void ModelController::slot_pluginSelected(const QString &pluginName) {
    //get bases of the plugin with that name and set the second dropdown in the dialog
    auto bases = mDataManager->getPluginBases(pluginName);
    mNewModelDialog->setAvailableBases(bases);
}

void ModelController::slot_projectPathUpdated() {
    mImportFilesWidget->clearModelList();
    mImportFilesWidget->addModels(mDataManager->getModelNamesOfCurrentProject());
}
