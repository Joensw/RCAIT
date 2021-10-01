/**
 * @file datamanager.h
 *
 * @brief functions for managing a classification dataset on disk
 *
 * @author various
 */
#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QStringList>
#include <QWidget>

#include "model/modelmanager.h"
#include "model/projectmanager.h"
#include "model/settingsmanager.h"
#include "trainingresult.h"
#include "classificationresult.h"

/**
 * @brief The DataManager class a facade to tie all the managers together and delegate to these
 */
class DataManager final {
public:

    /**
     * @brief DataManager deleted copy constructor
     */

    DataManager(const DataManager &) = delete;

    /**
     * @brief operator = deleted assignment operator
     */

    DataManager &operator=(const DataManager &) = delete;

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
    bool createNewProject(const QString& projectName, QString *error);

    /**
     * @brief removeProject deleted the project sub directory from the current projects directory.
     * @param projectName name of the project
     */
    void removeProject(const QString& projectName);

    /**
     * @brief loadProject loads the information of a project with a given name into the class so it can be accessed later.
     * @param projectName name of the project
     */
    /**
     * @brief loadProject loads the information of a project with a given name into the class so it can be accessed later.
     * @param projectName name of the project
     * @return true if the project could be loaded, false otherwise
     */
    bool loadProject(const QString& projectName);

    /**
     * @brief getProjectPath will return null string if no project is opened
     * @return absolute path to the currently opened project's subdirectory
     */
    QString getProjectPath();

    /**
     * @brief getProjectName get the name of the currently openend project, will return null string if no project is opened
     * @return name of the currently opened project
     */
    QString getProjectName();

    /**
     * @brief getProjectDataSetDir will return null string if no project is opened
     * @return absolute path to the data set directory of the currently opened project
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
     * @param paths list of paths to be verified
     * @return true if valid, false otherwise
     */
    static bool verifyPaths(const QStringList& paths);

    /**
     * @brief createNewModel created a new model with the specified parameters
     * @param modelName name of the model
     * @param pluginName name of the plugin the model is from
     * @param baseModel name of the base model to be used
     * @return true if the model could be created, false otherwise
     */
    bool createNewModel(QString modelName, QString pluginName, QString baseModel);

    /**
     * @brief removeModel removes a model according to the specified parameters
     * @param modelName name the model
     * @return true if the model was removed, false if an error occured
     */
    bool removeModel(QString modelName);

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
     * @return the currently loaded model
     */
    QString getCurrentModel();

    /**
     * @brief setLastWorkingDirectoryOfModel saves the given working directory to the model data
     * @param projectName the project name of the given model
     * @param modelName the name of the model to which the working directory belongs
     * @param workingDirectory the working directory to save
     */
    void saveLastWorkingDirectoryOfModel(const QString& projectName, const QString& modelName, const QString& workingDirectory);

    /**
     * @brief recallLastWorkingDirectoryOfModel returns the saved working directory of the given model
     * @param projectName the project name of the given model
     * @param modelName the name of model to which the working directory belongs
     * @return the saved working directory of the given model, if it exists, an empty QString otherwise
     */
    QString recallLastWorkingDirectoryOfModel(QString projectName, QString modelName);

    /**
     * @brief recallPluginNameOfModel find the plugin a certain model was derived from
     * @param projectName name of the project to search in
     * @param modelName name of the model to search by
     * @return name of the originating plugin
     */

    QString recallPluginNameOfModel(QString projectName, QString modelName);


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
    QStringList getPluginBases(const QString& plugin);

    /**
     * @return the input UI's of all the plugins
     */
    QList<QSharedPointer<QWidget>> getPluginSettings();

    /**
     * @brief savePluginSettings saves the settings of the plugin specified in the UI at the current index
     * @param index position of plugin settings widget
     */
    void savePluginSettings(int index);

    /**
     * @brief saveProjectsDir sets the value of the projects directory
     * @param dir the absolute path to the new projects directory
     */
    void saveProjectsDir(const QString& dir);

    /**
     * @return the absolute path to the current projects directory
     */
    QString getProjectsDir();

    /**
     * @brief saveClassificationPluginDir set the value of the classification plugin directory
     * @param dir the absolute path to the new projects directory
     */
    void saveClassificationPluginDir(const QString& dir);

    /**
     * @return the absolute path to the current classification plugin directory
     */
    QString getClassificationPluginDir();

    /**
     * @brief saveImageLoaderPluginDir set the value of the image loader plugin directory
     * @param dir the absolute path to the new projects directory
     */
    void saveImageLoaderPluginDir(const QString& dir);

    /**
     * @return the absolute path to the current image loader plugin directory
     */
    QString getImageLoaderPluginDir();


    /**
     * @return the absolute path to the current pythonge executable
     */

    QString getPythonExecutablePath();

    /**
     * @return the names of all loaded image loader plugins
     */
    QStringList getImageLoaderPluginNames();

    /**
     * @brief applyGlobalSettings changes the program paths according to parameters, if they are resolvable.
     * @param projectsDir the new projects directory
     * @param classificationPluginDir the new classification plugin directory
     * @param imageLoaderPluginDir the new image loader plugin directory
     * @param pythonPath the new python executable path
     * @param error optional argument, if an error occurs it will be written to here
     * @param pathChanged optional argument, the amount of paths updated will be written here
     * @return true if the new paths could be applied, false otherwise
     */
    bool applyGlobalSettings(const QString &projectsDir, const QString &classificationPluginDir, const QString &imageLoaderPluginDir,
                             const QString &pythonPath,
                             QString &error, int &pathsChanged);

    /**
     * @return return list of the training results that have been saved
     */
    QStringList getNamesOfSavedTrainingResults();

    /**
     * @return the input UI of the current classification plugin that is to be shown
     */
    QSharedPointer<QWidget> getInputWidget();

    /**
     * @return the input UI of the current classification plugins data augmentation settings that are to be shown
     */
    QSharedPointer<QWidget> getDataAugmentationInputWidget();

    /**
     * @brief getPluginIcons gets the icons of the plugins
     * @return the icons
     */
    QList<QSharedPointer<QIcon>> getPluginIcons();
    
private:
    ProjectManager *mProjectManager;
    ModelManager *mModelManager;
    SettingsManager *mSettingsManager;
    ConfigurationManager *mConfigurationManager;

    DataManager();
};


#endif //DATAMANAGER_H
