//
// Created by Paul on 02.07.2021.
//

#include "ProjectManager.h"
#include <QDir>
#include <QSettings>

ProjectManager::ProjectManager(){

}
void ProjectManager::createNewProject(QString projectName){
    //NOTE: the projects directory will also have to come from somewhere,
    //currently it is created one directory up from the build directory.


    //These will actually be defined elsewhere, such as the settings Manager
    const QString datasetDirName = "data";
    const QString tempDirName = "temp";

    //get list of all folders in project directory
    QDir projectsDir("../projects");
    projectsDir.setFilter(QDir::AllDirs | QDir::NoDotAndDotDot);
    QStringList projects = projectsDir.entryList();

    if (projects.contains(projectName)) {
        //Do something, this is not allowed
        //qDebug() << "Duplicate entry!";
        //return;
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

    newProjectfile.setValue("projectName", projectName);
    newProjectfile.setValue("projectDir", absolute);
    newProjectfile.setValue("datasetDirName", datasetDirName);
    newProjectfile.setValue("tempDirName", tempDirName);


}
void ProjectManager::removeProject(QString projectName){
    QDir targetDir("../projects/" + projectName);
    //removeRecursively deletes everything below also
    targetDir.removeRecursively();
}
void ProjectManager::loadProject(QString projectName){
    QString path = "../projects/" + projectName + "/" + projectName + ".ini";
    QSettings projectfile(path, QSettings::IniFormat);

    //todo replace strings with constants
    mProjectName = projectfile.value("projectName").toString();
    mProjectPath = projectfile.value("projectDir").toString();;
    mProjectPathDataSetDir = projectfile.value("datasetDirName").toString();;
    mProjectPathTempDir = projectfile.value("tempDirName").toString();;
}

QString ProjectManager::getProjectPath(){
    return mProjectPath;
}
QString ProjectManager::getProjectTempDir(){
    return mProjectPathTempDir;
}
QString ProjectManager::getProjectDataSetDir(){
    return mProjectPathDataSetDir;
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
