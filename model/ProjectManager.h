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
    QStringList getProjects();
    QString getProjectPath();
    QString getProjectTempDir();
    QString getProjectDataSetDir();
    QString getResultsDir();

    //todo doesnt have header yet/doesnt exist yet
    //void saveClassificationResult(ClasificationResult result);
    //void saveTrainingsResult(ClasificationResult result);
    //TrainingResult getTrainingsResult(Qstring modelResultName);
    QStringList getNamesOfSavedTrainingReults();





private:
    QString mProjectPath;
    QString mProjectTempDir;
    QString mProjectDataSetDir;
    QString mProjectResultsDir;
    QString mProjectName;
};


#endif //RCAIT_PROJECTMANAGER_H
