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
    DataManager(const DataManager&) = delete;

    DataManager& operator=(const DataManager&) = delete;

    /**
     * @brief getInstance returns the only instance of the DataManager class
     * @return instance
     */
    static DataManager &getInstance() {
        static DataManager instance; // Guaranteed to be destroyed.
        // Instantiated on first use.
        return instance;
    }
    
    /**
     * @return list of all directories in the projects directory
     */

    QStringList getProjects();

    /**
     * @brief createNewProject creates a new  project sub directory with the project name in the current projects directory.
     * @param projectName name of the new project
     */
    void createNewProject(QString projectName);

    /**
     * @brief createNewProject creates a new  project sub directory with the project name in the current projects directory. Preforms additional checks and writes an error message, should errors occur
     * @param projectName name of the new project
     * @param error pointer to where error messages can be written
     * @return true if a new project was created, false if there was an error
     */
    bool createNewProject(QString projectName, QString * error);

    /**
     * @brief removeProject deleted the project sub directory from the current projects directory.
     * @param projectName name of the project
     */
    void removeProject(QString projectName);

    /**
     * @brief loadProject loads the information of a project with a given name into the class so it can be accessed later.
     * @param projectName name of the project
     */
    void loadProject(QString projectName);

    /**
     * @brief getProjectPath will return null string if no project is opened
     * @return absolute path to the currently opened project's subdirectory
     */
    QString getProjectPath();

    /**
     * @brief getProjectName will return null string if no project is opened
     * @return name of the currently opened project
     */
    QString getProjectName();

    /**
     * @brief getProjectDataSetDir will return null string if no project is opened
     * @return absoulute path to the data set directory of the currently opened project
     */
    QString getProjectDataSetDir();

    /**
     * @return the absolute path to the validation images subfolder of the data set
     */
    QString getProjectDataSetValSubdir();

    /**
     * @return the absolute path to the training images subfolder of the data set
     */

    QString getProjectDataSetTrainSubdir();

    /**
     * @return the absolute path to the data augmentation temporary directory of the current project
     */

    QString getProjectAugTempDir();

    /**
     * @return the absolute path to the image temporary directory of the current project
     */

    QString getProjectImageTempDir();

    /**
     * The names receive the suffix _1, if this name is already taken, the suffix is incremented till it is available
     * @brief createWorkDirSubfolder creates a new subfolder in the working directory
     * @param name string argument, name of the folder
     * @return absolute path to the folder
     */

    QString createNewWorkSubDir(const QString &name);



    /**
     * The paths are valid, when they are not empty ie. "" or the nullstring, when they are not identical, and actually exist.
     * If the paths provided arent absolute there is no guarantee for whether the check passes or fails.
     *
     * @brief verifyDirectories check if the current set directories are valid
     * @return true if they are, false otherwise
     */

    bool verifyDirectories();

    /**
     * The paths are valid, when they are not empty ie. "" or the nullstring, when they are not identical, and actually exist.
     * If the paths provided arent absolute there is no guarantee for whether the check passes or fails.
     *
     * @brief verifyPaths check if the the specified directories would be considered valid by the application
     * @param projectsDirectory absolute path to the projects directory
     * @param classificationPluginDirectory absolute path the the classification plugin directory
     * @param imageLoaderDirectory absolute path to the image loader plugin directory
     * @return true if valid, false otherwise
     */
    bool verifyPaths(QString projectsDirectory, QString classificationPluginDirectory, QString imageLoaderDirectory);

    /**
     * @brief verifyPath check if a single path would be considered valid on it own
     * @param path the absolute path
     * @return true if valid, false otherwise
     */
    bool verifyPath(QString path);

    /**
     * @brief createNewModel created a new model with the specified parameters
     * @param modelName name of the model
     * @param pluginName name of the plugin the model is from
     * @param baseModel name of the base model to be used
     */
    void createNewModel(QString modelName, QString pluginName, QString baseModel);

    /**
     * @brief removeModel removes a model according to the specified parameters
     * @param modelName name the model
     */
    void removeModel(QString modelName);

    /**
     * @brief loadModel loads a model into the application for further use
     * @param modelName name of the model
     * @param pluginName name of the plugin the model is from
     */
    void loadModel(QString modelName, QString pluginName);

    /**
     * @return a list of all modelNames of the current project
     */
    QStringList getModelNamesOfCurrentProject();

    /**
     * @return the classification plugin the current model is from
     */
    QString getCurrentModel();

    /**
     * @brief setLastWorkingDirectoryOfModel saves the given working directory to the model data
     * @param projectName the project name of the given model
     * @param modelName the name of the model to which the working directory belongs
     * @param workingDirectory the working directory to save
     */
    void saveLastWorkingDirectoryOfModel(QString projectName, QString modelName, QString workingDirectory);

    /**
     * @brief recallLastWorkingDirectoryOfModel returns the saved working directory of the given model
     * @param projectName the project name of the given model
     * @param modelName the name of model to which the working directory belongs
     * @return the saved working directory of the given model, if it exists, an empty QString otherwise
     */
    QString recallLastWorkingDirectoryOfModel(QString projectName, QString modelName);


    QString recallPluginNameOfModell(QString projectName, QString modelName);



    /**
     * @return the classification plugin the current model is from
     */
    QString getCurrentClassificationPlugin();

    /**
     * @return a list of the names of all the plugins that were loaded
     */
    QStringList getPluginNames();

    /**
     * @return the names of all loaded classification plugins
     */
    QStringList getClassificationPluginNames();

    /**
     * @param plugin the classification plugin
     * @return list of the bases of a particular classification plugin
     */
    QStringList getPluginBases(QString plugin);

    /**
     * @return the input UI's of all the plugins
     */
    QList<QWidget*> getPluginSettings();

    /**
     * @brief savePluginSettings saves the settings of the plugin specified in the UI at the current index
     * @param index position of plugin settings widget
     */
    void savePluginSettings(int index);

    /**
     * @brief saveProjectsDir sets the value of the projects directory
     * @param dir the absolute path to the new projects directory
     */
    void saveProjectsDir(QString dir);

    /**
     * @return the absolute path to the current projects directory
     */
    QString getProjectsDir();

    /**
     * @brief saveClassificationPluginDir set the value of the classification plugin directory
     * @param dir the absolute path to the new projects directory
     */
    void saveClassificationPluginDir(QString dir);

    /**
     * @return the absolute path to the curent classifcation plugin directory
     */
    QString getClassificationPluginDir();

    /**
     * @brief saveImageLoaderPluginDir set the value of the image loader plugin directory
     * @param dir the absolute path to the new projects directory
     */
    void saveImageLoaderPluginDir(QString dir);

    /**
     * @return the absolute path to the current image loader plugin directory
     */
    QString getImageLoaderPluginDir();

    /**
     * @return the names of all loaded image loader plugins
     */
    QStringList getImageLoaderPluginNames();

    /**
     * @brief applyGlobalSettings changes the program paths acording to parameters, if they are resolvable.
     * @param projectsDir the new projects directory
     * @param classificationPluginDir the new classification plugin directory
     * @param imageLoaderPluginDir the new image loader pluign directory
     * @param error optional argument, if an error occurs it will be written to here
     * @param pathChanged optional argument, the amount of paths updated will be written here
     * @return true if the new paths could be applied, false otherwise
     */
    bool applyGlobalSettings(QString projectsDir, QString classificationPluginDir, QString imageLoaderPluginDir,
                             QString * error = nullptr, int * pathsChanged = nullptr);
    /**
     * @return return list of the training results that have been saved
     */
    QStringList getNamesOfSavedTrainingResults();

    /**
     * @return the input UI of the current classification plugin that is to be shown
     */
    QWidget *getInputWidget();

    /**
     * @return the input UI of the current classification plugins data augmentation settings that are to be shown
     */
    QWidget * getDataAugmentationInputWidget();
    
private:
    ProjectManager* mProjectManager;
    ModelManager* mModelManager;
    SettingsManager* mSettingsManager;

    DataManager();
};


#endif //DATAMANAGER_H
