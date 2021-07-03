//
// Created by Paul on 02.07.2021.
//

#ifndef RCAIT_DATAMANAGER_H
#define RCAIT_DATAMANAGER_H

#include <QStringList>
#include <QWidget>

class DataManager {
public:
    DataManager();

    QStringList getProjects();
    void createNewProject(QString projectName);
    void removeProject(QString projectName);
    void loadProject(QString projectName);
    QString getProjectPath();
    QString getProjectTempDir();
    QString getProjectDataSetDir();


    void createNewModel(QString modelName, QString pluginName, QString baseModel);
    void removeModel(QString modelName, QString pluginName);
    void loadModel(QString modelName, QString pluginName);
    QString getCurrentModel();
    QString getCurrentClassificationPlugin();

    QStringList getPluginNames();
    QList<QWidget*> getPluginSettings();
    void savePluginSettings(int index);
    void saveProjectsDir(QString value);
    QString getProjectsDir();
    void saveClassificationPluginDir(QString value);
    QString getClassificationPluginDir();
    void saveImageLoaderPluginDir(QString value);
    QString getImageLoaderPluginDir();

    //todo doesnt have header yet/doesnt exist yet
    //void saveClassificationResult(ClasificationResult result);
    //void saveTrainingsResult(ClasificationResult result);
    //TrainingResult getTrainingsResult(Qstring modelResultName);
    QStringList getNamesOfSavedTrainingReults();


};


#endif //RCAIT_DATAMANAGER_H
