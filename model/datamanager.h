#ifndef DATAMANAGER_H
#define DATAMANAGER_H

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
    QString getProjectPath(); //maybe give these the prefix openProject to avoid confusion with the getters for the directories
    QString getProjectTempDir(); //
    QString getProjectDataSetDir(); //
    bool verifyDirectories();
    bool verifyPaths(QString projectsDirectory, QString classificationPluginDirectory, QString imageLoaderDirectory);
    bool verifyPath(QString path);

    void createNewModel(QString modelName, QString pluginName, QString baseModel);
    void removeModel(QString modelName, QString pluginName);
    void loadModel(QString modelName, QString pluginName);
    QString getCurrentModel();
    QString getCurrentClassificationPlugin();

    QStringList getPluginNames();
    QStringList getClassificationPluginNames();
    QStringList getPluginBases(QString plugin);
    QList<QWidget*> getPluginSettings();
    void savePluginSettings(int index);
    void saveProjectsDir(QString value);
    QString getProjectsDir();
    void saveClassificationPluginDir(QString value);
    QString getClassificationPluginDir();
    void saveImageLoaderPluginDir(QString value);
    QString getImageLoaderPluginDir();

    void saveClassificationResult(ClassificationResult result);
    void saveTrainingsResult(TrainingResult result);
    TrainingResult getTrainingsResult(QString modelResultName);
    QStringList getNamesOfSavedTrainingResults();

private:
    //TODO: Singleton adaption
    ProjectManager* mProjectManager;
    ModelManager* mModelManager;
    SettingsManager* mSettingsManager;
};


#endif //DATAMANAGER_H
