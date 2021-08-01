#include "projectcontroller.h"
#include <QRegularExpression>
#include <QDir>

ProjectController::ProjectController(QObject *parent, DataManager * dataManager, StartWidget *startWidget) : QObject(parent)
{
    this->mDataManager = dataManager;
    this->mStartWidget = startWidget;
    connect(mStartWidget, &StartWidget::sig_newProject, this, &ProjectController::slot_newProject);
    connect(mStartWidget, &StartWidget::sig_removeProject, this, &ProjectController::slot_removeProject);
    connect(mStartWidget, &StartWidget::sig_openProject, this, &ProjectController::slot_openProject);
    startWidget->addProjects(mDataManager->getProjects());
}

void ProjectController::refresh()
{
    mStartWidget->clearProjectList();
    mStartWidget->addProjects(mDataManager->getProjects());
}

void ProjectController::slot_newProject(){
    mNewProjectDialog = new NewProjectDialog();
    mNewProjectDialog->setAttribute(Qt::WA_DeleteOnClose, true);
    mNewProjectDialog->setModal(true);
    connect(mNewProjectDialog, &NewProjectDialog::sig_newProjectConfirm, this, &ProjectController::slot_newProjectConfirm);
    mNewProjectDialog->show();
}

void ProjectController::slot_removeProject(QString projectName){
    mRemoveProjectDialog = new RemoveProjectDialog(nullptr, projectName);
    mRemoveProjectDialog->setAttribute(Qt::WA_DeleteOnClose, true);
    mRemoveProjectDialog->setModal(true);
    connect(mRemoveProjectDialog, &RemoveProjectDialog::sig_removeProjectConfirm, this, &ProjectController::slot_removeProjectConfirm);
    mRemoveProjectDialog->show();
}

void ProjectController::slot_openProject(QString projectName){
    mDataManager->loadProject(projectName);
    emit sig_projectPathUpdated();
}

void ProjectController::slot_projectDirectoryChanged()
{
    refresh();
}

void ProjectController::slot_newProjectConfirm(QString projectName)
{
    QString error;
    if (!mDataManager->createNewProject(projectName, &error)){
        mNewProjectDialog->setErrorMessage(error);
        mNewProjectDialog->showErrorMessage();
        return;
    }
    mStartWidget->addProject(projectName);
    mNewProjectDialog->close();
}

void ProjectController::slot_removeProjectConfirm()
{
    mDataManager->removeProject(mRemoveProjectDialog->getProjectName());
    mStartWidget->clearProjectList();
    mStartWidget->addProjects(mDataManager->getProjects());
    mRemoveProjectDialog->close();
}
