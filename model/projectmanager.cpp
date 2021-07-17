#include "projectmanager.h"
#include <QDir>
#include <QSettings>
#include <QRegularExpression>


QString projectDirectory = "../projects";

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

QStringList ProjectManager::getProjects() {
    QDir projectsDir(mProjectsDirectory);
    projectsDir.setFilter(QDir::AllDirs | QDir::NoDotAndDotDot);
    return projectsDir.entryList();
}

void ProjectManager::createNewProject(QString projectName) {
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
    newProjectfile.setValue(projectDirectoryIdentifier_projectsFile, absolute);
    newProjectfile.setValue(projectDatasetDirectoryIdentifier, datasetDirectoryName);
    newProjectfile.setValue(projectTempDirectoryIdentifier, tempDirectoryName);

    //make temp and Data subdirectories
    QDir dir;
    dir.mkpath(absolute + "/" +  datasetDirectoryName);
    dir.mkpath(absolute + "/" + tempDirectoryName);
    dir.mkpath(absolute + "/" +  resultsDirectoryName);
}

void ProjectManager::removeProject(QString projectName) {
    QDir targetDir(mProjectsDirectory + "/" + projectName);
    targetDir.removeRecursively();
}

void ProjectManager::loadProject(QString projectName) {
    //QString path = "../projects/" + projectName + "/" + projectName + ".ini";
    QString loadProjectPath = mProjectsDirectory + "/" + projectName + "/" + projectName + ".ini";

    QSettings projectfile(loadProjectPath, QSettings::IniFormat);

    //todo replace strings with constants
    mProjectName = projectfile.value(projectNameIdentifier).toString();
    mProjectPath = projectfile.value(projectDirectoryIdentifier_projectsFile).toString();
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

void ProjectManager::saveTrainingsResult(ClassificationResult result) {

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



