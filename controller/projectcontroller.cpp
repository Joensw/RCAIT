/**
 * @file projectcontroller.cpp
 *
 * @brief connects the logic of the project management with the user interface
 *
 * @author Jonas Wille
 */
#include "projectcontroller.h"

ProjectController::ProjectController(QObject *parent, DataManager *dataManager, StartWidget *startWidget)
        : QObject(parent),
          mDataManager(dataManager),
          mStartWidget(startWidget) {

    connect(mStartWidget, &StartWidget::sig_newProject, this, &ProjectController::slot_newProject);
    connect(mStartWidget, &StartWidget::sig_removeProject, this, &ProjectController::slot_removeProject);
    connect(mStartWidget, &StartWidget::sig_openProject, this, &ProjectController::slot_openProject);
    startWidget->addProjects(mDataManager->getProjects());
}

void ProjectController::refresh() {
    mStartWidget->clearProjectList();
    mStartWidget->addProjects(mDataManager->getProjects());
}

void ProjectController::slot_newProject() {
    mNewProjectDialog = new NewProjectDialog;
    mNewProjectDialog->setAttribute(Qt::WA_DeleteOnClose, true);
    mNewProjectDialog->setModal(true);
    connect(mNewProjectDialog, &NewProjectDialog::sig_newProjectConfirm, this,
            &ProjectController::slot_newProjectConfirm);
    mNewProjectDialog->show();
}

void ProjectController::slot_removeProject(QString projectName) {
    mRemoveProjectDialog = new RemoveProjectDialog(nullptr, std::move(projectName));
    mRemoveProjectDialog->setAttribute(Qt::WA_DeleteOnClose, true);
    mRemoveProjectDialog->setModal(true);
    connect(mRemoveProjectDialog, &RemoveProjectDialog::sig_removeProjectConfirm, this,
            &ProjectController::slot_removeProjectConfirm);
    mRemoveProjectDialog->show();
}

void ProjectController::slot_openProject(QString projectName) {
    mDataManager->loadProject(std::move(projectName));
    emit sig_projectPathUpdated();
}

void ProjectController::slot_projectDirectoryChanged() {
    refresh();
}

void ProjectController::slot_newProjectConfirm(QString projectName) {
    QString error;
    if (!mDataManager->createNewProject(std::move(projectName), &error)) {
        mNewProjectDialog->setErrorMessage(error);
        mNewProjectDialog->showErrorMessage();
        return;
    }
    refresh();
    mNewProjectDialog->close();
}

void ProjectController::slot_removeProjectConfirm() {
    if (!(mRemoveProjectDialog->getProjectName() == mDataManager->getProjectName())){
        mDataManager->removeProject(mRemoveProjectDialog->getProjectName());
        mStartWidget->clearProjectList();
        mStartWidget->addProjects(mDataManager->getProjects());
        mRemoveProjectDialog->close();
        return;
    }
    mRemoveProjectDialog->setErrorMessage(OPEN_PROJECT_ERROR);
}
