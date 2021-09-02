#ifndef PROJECTMANAGER_H
#define PROJECTMANAGER_H

#include <QString>
#include <QObject>
#include "classificationresult.h"
#include "trainingresult.h"

//Names of the subfolders in the project directory
//These can be changed.
//Make sure to choose names that are not disallowed in windows ar under linux!
extern const QString resultsDirectoryName;
extern const QString datasetDirectoryName;
extern const QString tempImagesDirectoryName;
extern const QString tempDataAugDirectoryName;
extern const QString trainingsResultsDirectoryName;
extern const QString classificationResultsDirectoryName;

//keys of the <String, String> pair in the project file
extern const QString projectNameIdentifier;
extern const QString projectDatasetDirectoryIdentifier;
extern const QString projectValidationDatasetIdentifier;
extern const QString projectTrainingDatasetIdentifier;
extern const QString projectTempImagesDirectoryIdentifier;
extern const QString projectTempDataAugDirectoryIdentifier;
extern const QString projectResultsDirectoryIdentifier;
extern const QString projectTrainingsResultsDirectoryIdentifer;
extern const QString projectClassificationResultsDirectoryIdentifier;
extern const QString projectWorkingDirIdentifier;

extern const QString validiationDatasetDirectoryName;
extern const QString trainingDatasetDirectoryName;

extern const QString workingDirectoryName;

//filetype the project file has
extern const QString projectFileType;

/**
 * @brief The ProjectManager class contains the logic for manipulating the projects of the application
 */
class ProjectManager{
public:
    //Threadsafe Singleton pattern
    ProjectManager(ProjectManager const &) = delete;

    void operator=(ProjectManager const &) = delete;

    /**
     * @brief getInstance returns the only instance of the ProjectManager class
     * @return instance
     */
    static ProjectManager &getInstance() {
        static ProjectManager instance; // Guaranteed to be destroyed.
        // Instantiated on first use.
        return instance;
    }

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
    bool createNewProject(const QString &projectName, QString * error);

    /**
     * @brief removeProject deleted the project sub directory from the current projects directory.
     * @param projectName name of the project
     */
    void removeProject(const QString &projectName);

    /**
     * @brief loadProject loads the information of a project with a given name into the class so it can be accessed later.
     * @param projectName name of the project
     */
    void loadProject(const QString &projectName);

    /**
     * @return list of all directories in the projects directory
     */
    QStringList getProjects();

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
     * @brief getProjectImageTempDir will return null string if no project is opened
     * @return the absolute path to the image temporary directory of the current project
     */

    QString getProjectImageTempDir();

    /**
     * @brief getProjectAugTempDir will return null string if no project is opened
     * @return the absolute path to the data augmentation temporary directory of the current project
     */

    QString getProjectAugTempDir();

    /**
     * @brief getResultsDir will return null string if no project is opened
     * @return absolute path to the results directroy of the currently opened project
     */
    QString getResultsDir();

    /**
     * @brief getTrainingResultsDir will return null string if no project is opened
     * @return  absolute path to the trainings results subdirectory of the currently opened project
     */
    QString getTrainingResultsDir();

    /**
     * @brief getClassificationResultsDir will return null string if no project is opened
     * @return absolute path to the classification results subdirectory of the currently opened project
     */
    QString getClassificationResultsDir();

    /** Only .txt files are returned and within the list they have no file ending, if no project is opened an empty list is returned
     * @return getNamesOfSavedTrainingResults returns the names of all the files in the trainings results folder
     */
    QStringList getNamesOfSavedTrainingResults();

    /**
     * The names receive the suffix _1, if this name is already taken, the suffix is incremented till it is available
     * @brief createWorkDirSubfolder creates a new subfolder in the working directory
     * @param name string argument, name of the folder
     * @return absolute path to the folder
     */
    QString createWorkDirSubfolder(const QString &name);

    /**
     * @brief setProjectsDirectory sets the  projects directory, ie. the directory projects are to be created, deleted and loaded from
     * @param newDirectory the new projects directory
     */
    void setProjectsDirectory(const QString &newDirectory);

private:
    bool verifyName(QString projectName, QString * error);

    QString mProjectPath;
    QString mProjectImagesTempDir;
    QString mProjectAugTempDir;
    QString mProjectDataSetDir;
    QString mProjectDataSetValSubdir;
    QString mProjectDataSetTrainSubdir;
    QString mProjectResultsDir;
    QString mProjectTrainingResultsDir;
    QString mProjectClassificationResultsDir;
    QString mProjectName;
    QString mProjectWorkingDir;

    QString mProjectsDirectory;

    ProjectManager();
};


#endif //PROJECTMANAGER_H
