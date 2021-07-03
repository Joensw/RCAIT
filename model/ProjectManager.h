//
// Created by Paul on 02.07.2021.
//

#ifndef RCAIT_PROJECTMANAGER_H
#define RCAIT_PROJECTMANAGER_H

#include <QString>


class ProjectManager {
public:
    ProjectManager();

    void createNewProject(QString projectName);
    void removeProject(QString projectName);
    void loadProject(QString projectName);
    QString getProjectPath();
    QString getProjectTempDir();
    QString getProjectDataSetDir();

    //todo doesnt have header yet/doesnt exist yet
    //void saveClassificationResult(ClasificationResult result);
    //void saveTrainingsResult(ClasificationResult result);
    //TrainingResult getTrainingsResult(Qstring modelResultName);
    QStringList getNamesOfSavedTrainingReults();





private:
    QString projectPath;
    QString projectPathTempDir;
    QString projectPathDataSetDir;
    QString projectName;


};


#endif //RCAIT_PROJECTMANAGER_H
