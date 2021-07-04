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



    /* goes into the projects folder, then into the specific project folder
     * there it creates a new ini file, which can be seen as the "project file"
     */


    QSettings newProjectfile(path, QSettings::IniFormat);

    //this is only to get an absolute path, without .. and .
    QDir projectDir(QFileInfo(path).absoluteDir());
    QString absolute = projectDir.absolutePath();

    newProjectfile.setValue("projectName", projectName);
    newProjectfile.setValue("projectDir", absolute);
    newProjectfile.setValue("datasetDirName", datasetDirName);
    newProjectfile.setValue("tempDirName", tempDirName);

    //non existing folders / directories will be automatically created
}
//Lösche Projektdatei ordner
void ProjectManager::removeProject(QString projectName){

}
//informationen aus der projectDatei wird in die klassen attribute übernommen, mittels qsettings geht das ganz gut
void ProjectManager::loadProject(QString projectName){

}

QString ProjectManager::getProjectPath(){
    return projectPath;
}
QString ProjectManager::getProjectTempDir(){
    return projectPathTempDir;
}
QString ProjectManager::getProjectDataSetDir(){
    return projectPathDataSetDir;
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
