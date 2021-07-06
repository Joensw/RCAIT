#include "projectcontroller.h"
#include <QRegularExpression>
#include <QDir>

ProjectController::ProjectController()
{

}

bool ProjectController::verifyName(QString input)
{
    //check if name is invalid
    if (input.length() == 0){
        return false;
    }

    //check if name comtains special characters
    QRegularExpression rx1("^[A-Za-z0-9]+$");
    QRegularExpressionMatch match = rx1.match(input);
    if (!match.hasMatch()) {
        return false;
    }

    //check if name is already taken
    QDir projectsDir("../projects");
    projectsDir.setFilter(QDir::AllDirs | QDir::NoDotAndDotDot);
    QStringList projects = projectsDir.entryList();
    if (projects.contains(input)) {
        return false;
    }
    return true;
}

void ProjectController::newProjectConfirm(QString projectName)
{

}
