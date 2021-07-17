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
    QString getProjectPath();
    QString getProjectTempDir();
    QString getProjectDataSetDir();
    bool verifyDirectories(); //is new was not in UML, is needed to check if paths currently stored for the directories are valid
    bool verifyPaths(QString projectsDirectory, QString classificationPluginDirectory, QString imageLoaderDirectory); //is new was not in UML, is needed to check if path candidates are valid
    bool verifyPath(QString path); //is new was not in UML, is needed to by settings manager to check paths indivually

    void createNewModel(QString modelName, QString pluginName, QString baseModel);
    void removeModel(QString modelName, QString pluginName);
    void loadModel(QString modelName, QString pluginName);
    QString getCurrentModel();
    QString getCurrentClassificationPlugin();

    QStringList getPluginNames();
    QStringList getClassificationPluginNames(); //is new was not in UML, is needed on importfile widget to show available classification plugins
    QStringList getPluginBases(QString plugin); //is new was not in UML, is needed on the newModelDialog to show the bases for a specific plugin
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
    QStringList getNamesOfSavedTrainingResults();

private:
    //TODO: Singleton adaption
    ProjectManager* mProjectManager;
    ModelManager* mModelManager;
    SettingsManager* mSettingsManager;
};


#endif //DATAMANAGER_H
