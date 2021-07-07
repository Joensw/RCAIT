#include "projectcontroller.h"
#include <QRegularExpression>
#include <QDir>

ProjectController::ProjectController(QObject *parent, DataManager * dataManager, StartWidget *startWidget) : QObject(parent)
{
    this->mDataManager = dataManager;
    this->mStartWidget = startWidget;
    connect(mStartWidget, &StartWidget::sig_openNewProjectDialog, this, &ProjectController::slot_newProject);
    qDebug() << mDataManager->getProjects();
    startWidget->addProjects(mDataManager->getProjects());
}

QString ProjectController::verifyName(QString input)
{
    QString output = "";
    //check if name is invalid
    if (input.length() == 0){
        output.append("Name must contain at least 1 character\n");
    }

    //check if name comtains special characters
    QRegularExpression rx1("^[\\w]*$");
    QRegularExpressionMatch match = rx1.match(input);
    if (!match.hasMatch()) {
        output.append("Name may not contain special characters\n");
    }

    //check if name is already taken
    QDir projectsDir("../projects");
    projectsDir.setFilter(QDir::AllDirs | QDir::NoDotAndDotDot);
    QStringList projects = projectsDir.entryList();
    if (projects.contains(input)) {
        output.append("A project with this name aleady exists in the project Directory");
    }
    return output;
}

void ProjectController::slot_newProject(){
    mNewProjectDialog = new NewProjectDialog();
    mNewProjectDialog->setAttribute(Qt::WA_DeleteOnClose, true);
    connect(mNewProjectDialog, &NewProjectDialog::sig_newProjectConfirm, this, &ProjectController::slot_newProjectConfirm);
    mNewProjectDialog->show();
}

void ProjectController::slot_newProjectConfirm(QString projectName)
{
    QString error = verifyName(projectName);
    if (!error.isEmpty()){
        mNewProjectDialog->setErrorMessage(error);
        mNewProjectDialog->showErrorMessage();
        return;
    }
    mDataManager->createNewProject(projectName);
    mStartWidget->addProject(projectName);
    mNewProjectDialog->close();
}
