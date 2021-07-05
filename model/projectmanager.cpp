//
// Created by Paul on 02.07.2021.
//

#include "projectmanager.h"
#include <QDir>
#include <QSettings>
#include <QRegularExpression>


QString projectDirectory = "../projects";
QString initializeString = "";
QString resultsDirectoryName = "results";

//on creation, meaning program startup, there will be no project selected.
ProjectManager::ProjectManager(){
    mProjectPath = initializeString;
    mProjectTempDir = initializeString;
    mProjectDataSetDir = initializeString;
    mProjectName = initializeString;
}

QStringList ProjectManager::getProjects(){
    QDir projectsDir(projectDirectory);
    projectsDir.setFilter(QDir::AllDirs | QDir::NoDotAndDotDot);
    return projectsDir.entryList();
}

void ProjectManager::createNewProject(QString projectName){
    //NOTE: the projects directory will also have to come from somewhere,
    //currently it is created one directory up from the build directory.


    //These will actually be defined elsewhere, such as the settings Manager
    const QString datasetDirName = "data";
    const QString tempDirName = "temp";

    //check if name is invalid
    if (projectName == initializeString){
        //do something, not allowed
    }

    //check if name comtains special characters
    QRegularExpression rx1("^[A-Za-z0-9]+$");
    QRegularExpressionMatch match = rx1.match(projectName);
    if (!match.hasMatch()) {
        //do something, not allowed
    }

    //check if name is already taken
    QDir projectsDir("../projects");
    projectsDir.setFilter(QDir::AllDirs | QDir::NoDotAndDotDot);
    QStringList projects = projectsDir.entryList();
    if (projects.contains(projectName)) {
        //do something, not allowed
    }


    QString path = "../projects/" + projectName + "/" + projectName + ".ini";



     /*goes into the projects folder, then into the specific project folder
     * there it creates a new ini file, which can be seen as the "project file"
     */


    //non existing folders / directories will be automatically created
    QSettings newProjectfile(path, QSettings::IniFormat);

    //this is only to get an absolute path, without .. and .
    QDir projectDir(QFileInfo(path).absoluteDir());
    QString absolute = projectDir.absolutePath();
    absolute.append("/");

    //todo replace stings with cosntants
    newProjectfile.setValue("projectName", projectName);
    newProjectfile.setValue("projectDir", absolute);
    newProjectfile.setValue("datasetDirName", datasetDirName);
    newProjectfile.setValue("tempDirName", tempDirName);

    //make temp and Data subdirectories
     QDir dir;
     dir.mkpath(absolute + datasetDirName);
     dir.mkpath(absolute + tempDirName);
     dir.mkpath(absolute + resultsDirectoryName);

}
void ProjectManager::removeProject(QString projectName){
    QDir targetDir("../projects/" + projectName );
    //removeRecursively deletes everything in the directory
    targetDir.removeRecursively();
}
void ProjectManager::loadProject(QString projectName){
    QString path = "../projects/" + projectName + "/" + projectName + ".ini";
    QSettings projectfile(path, QSettings::IniFormat);

    //todo replace strings with constants
    mProjectName = projectfile.value("projectName").toString();
    mProjectPath = projectfile.value("projectDir").toString();
    mProjectDataSetDir = mProjectPath + projectfile.value("datasetDirName").toString();
    mProjectTempDir = mProjectPath + projectfile.value("tempDirName").toString();
    mProjectResultsDir = mProjectPath + resultsDirectoryName;
}

QString ProjectManager::getProjectPath(){
    return mProjectPath;
}
QString ProjectManager::getProjectTempDir(){
    return mProjectTempDir;
}
QString ProjectManager::getProjectDataSetDir(){
    return mProjectDataSetDir;
}
QString ProjectManager::getResultsDir(){
    return mProjectResultsDir;
}

/* TODO GIBTS NOCH NICHT
//speichere in einem Unterordner ab
void ProjectManager::saveClassificationResult(ClasificationResult result){

}
//speichere auch in einem unter orderner ab
void ProjectManager::saveTrainingsResult(ClasificationResult result){

}
//hole aus ordner heraus
void ProjectManager::getTrainingsResult(QString modelResultName){

}
//indiziere unterOrdner
QStringList ProjectManager::getNamesOfSavedTrainingReults(){

}
*/
