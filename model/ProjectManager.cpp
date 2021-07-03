//
// Created by Paul on 02.07.2021.
//

#include "ProjectManager.h"
#include <QDir>

ProjectManager::ProjectManager(){

}

//Legt neue Projektdatei an, im projekt ordner in seinem eigenen Verzeichnis

void ProjectManager::createNewProject(QString projectName){
/*
    //CHECK NAME UNIQUE;

    QString path("projects" + "/" + projectName);
    QDir dir;

    if (!dir.exists(path)) {
        dir.mkpath(path);
    }

    QFile file(path + projectName + "/" + "projectName");
    file.open(QIODevice::WriteOnly);

    //Parse n stuff

    WORK IN PROGRESS
*/
}
//Lösche Projektdatei, ordner
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
