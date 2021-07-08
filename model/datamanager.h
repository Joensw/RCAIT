//
// Created by Paul on 02.07.2021.
//

#ifndef RCAIT_DATAMANAGER_H
#define RCAIT_DATAMANAGER_H

#include <QStringList>
#include <QWidget>

#include "model/modelmanager.h"
#include "model/projectmanager.h"
#include "model/settingsmanager.h"
#include "trainingresult.h"
#include "classificationresult.h"

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

    void saveClassificationResult(ClassificationResult result);
    void saveTrainingsResult(ClassificationResult result);
    TrainingResult getTrainingsResult(QString modelResultName);
    QStringList getNamesOfSavedTrainingReults();

private:
    ProjectManager* mProjectManager;
    ModelManager* mModelManager;
    SettingsManager* mSettingsManager;
};


#endif //RCAIT_DATAMANAGER_H
