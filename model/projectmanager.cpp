#include "projectmanager.h"
#include <QDir>
#include <QSettings>
#include <QRegularExpression>


//names of the subfolders in the project directory
//NOTE: it should be possible to change these, havent tested this yet
QString resultsDirectoryName = "results";
QString datasetDirectoryName = "data";
QString tempDirectoryName = "temp";

//keys of the <String, String> pair in the project file
QString projectNameIdentifier = "projectName";
QString projectDirectoryIdentifier_projectsFile = "projectDir";
QString projectDatasetDirectoryIdentifier = "datasetDirName";
QString projectTempDirectoryIdentifier = "tempDirName";

//on creation, meaning program startup, there will be no project selected. all the strings will be null/empty
ProjectManager::ProjectManager() {

}

void ProjectManager::createNewProject(QString projectName)
{
    QString newProjectPath = mProjectsDirectory + "/" + projectName + "/" + projectName + ".ini";

    /*goes into the projects folder, then into the specific project folder
    * there it creates a new ini file, which can be seen as the "project file"
    */

    //non existing folders / directories will be automatically created
    QSettings newProjectfile(newProjectPath, QSettings::IniFormat);

    //this is only to get an absolute path, without .. and .
    QDir projectDir(QFileInfo(newProjectPath).absoluteDir());
    QString absolute = projectDir.absolutePath();

    newProjectfile.setValue(projectNameIdentifier, projectName);
    //newProjectfile.setValue(projectDirectoryIdentifier_projectsFile, absolute);
    newProjectfile.setValue(projectDatasetDirectoryIdentifier, datasetDirectoryName);
    newProjectfile.setValue(projectTempDirectoryIdentifier, tempDirectoryName);

    //make temp and Data subdirectories
    QDir dir;
    dir.mkpath(absolute + "/" +  datasetDirectoryName);
    dir.mkpath(absolute + "/" + tempDirectoryName);
    dir.mkpath(absolute + "/" +  resultsDirectoryName);
}

QStringList ProjectManager::getProjects() {
    if (!mProjectsDirectory.isEmpty()){
        QDir projectsDir(mProjectsDirectory);
        projectsDir.setFilter(QDir::AllDirs | QDir::NoDotAndDotDot);
        return projectsDir.entryList();
    }
    QStringList empty;
    return empty;
}

bool ProjectManager::createNewProject(QString projectName, QString * error) {
    if (!verifyName(projectName, error)){
        return false;
    }
    createNewProject(projectName);
    return true;
}

void ProjectManager::removeProject(QString projectName) {
    QDir targetDir(mProjectsDirectory + "/" + projectName);
    targetDir.removeRecursively();
}

void ProjectManager::loadProject(QString projectName) {
    QString loadProjectPath = mProjectsDirectory + "/" + projectName + "/" + projectName + ".ini";

    QSettings projectfile(loadProjectPath, QSettings::IniFormat);

    mProjectName = projectfile.value(projectNameIdentifier).toString();
    mProjectPath = mProjectsDirectory + "/" + projectName;
    //mProjectPath = projectfile.value(projectDirectoryIdentifier_projectsFile).toString();
    mProjectDataSetDir = mProjectPath + "/" + projectfile.value(projectDatasetDirectoryIdentifier).toString();
    mProjectTempDir = mProjectPath + "/" + projectfile.value(projectTempDirectoryIdentifier).toString();
    mProjectResultsDir = mProjectPath + "/" + resultsDirectoryName;
}

QString ProjectManager::getProjectPath() {
    return mProjectPath;
}

QString ProjectManager::getProjectTempDir() {
    return mProjectTempDir;
}

QString ProjectManager::getProjectDataSetDir() {
    return mProjectDataSetDir;
}

QString ProjectManager::getResultsDir() {
    return mProjectResultsDir;
}

void ProjectManager::saveClassificationResult(ClassificationResult result) {

}

void ProjectManager::saveTrainingsResult(TrainingResult result) {

}

TrainingResult ProjectManager::getTrainingsResult(QString modelResultName) {

}

QStringList ProjectManager::getNamesOfSavedTrainingResults() {
    QStringList l;
    return l;
}

void ProjectManager::setProjectsDirectory(QString newDirectory)
{
    mProjectsDirectory = newDirectory;
}

bool ProjectManager::verifyName(QString input, QString *error)
{
    bool status = true;
    if (input.length() == 0){
        error->append(QObject::tr("Name must contain at least 1 character") +"\n");
        status = false;
    }

    //check if name comtains special characters
    QRegularExpression rx1("^[\\w]*$");
    QRegularExpressionMatch match = rx1.match(input);
    if (!match.hasMatch()) {
        error->append(QObject::tr("Name may not contain special characters") + "\n");
        status = false;
    }

    //check if name is already taken
    QDir projectsDir(mProjectsDirectory);
    projectsDir.setFilter(QDir::AllDirs | QDir::NoDotAndDotDot);
    QStringList projects = projectsDir.entryList();
    if (projects.contains(input)) {
        error->append(QObject::tr("A project with this name aleady exists in the project directory"));
        status = false;

    }
    return status;
}



