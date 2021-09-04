#ifndef PROJECTMANAGER_H
#define PROJECTMANAGER_H

#include <QString>
#include <QObject>
#include <ce_string.h>
#include "classificationresult.h"
#include "trainingresult.h"

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
    //Names of the subfolders in the project directory
    //These can be changed.
    //Make sure to choose names that are not disallowed in windows ar under linux!
    static constexpr CE_String resultsDirectoryName = "results";
    static constexpr CE_String datasetDirectoryName = "data";
    static constexpr CE_String tempImagesDirectoryName = "temp_Images";
    static constexpr CE_String tempDataAugDirectoryName = "temp_Aug";
    static constexpr CE_String trainingsResultsDirectoryName = "training_results";
    static constexpr CE_String classificationResultsDirectoryName = "classification_results";
    static constexpr CE_String  validiationDatasetDirectoryName = "validation";
    static constexpr CE_String  trainingDatasetDirectoryName = "training";
    static constexpr CE_String workingDirectoryName = "working_directory";

    //keys of the <String, String> pair in the project file
    static constexpr CE_String projectNameIdentifier = "projectName";
    static constexpr CE_String projectDatasetDirectoryIdentifier = "datasetDirName";
    static constexpr CE_String projectValidationDatasetIdentifier = "validationDatasetDirName";
    static constexpr CE_String projectTrainingDatasetIdentifier = "trainingDatasetDirName";
    static constexpr CE_String projectTempImagesDirectoryIdentifier = "tempImagesDirName";
    static constexpr CE_String projectTempDataAugDirectoryIdentifier = "tempDataAugDirName";
    static constexpr CE_String projectResultsDirectoryIdentifier = "resultsDirName";
    static constexpr CE_String projectTrainingsResultsDirectoryIdentifer = "trainingResultsDirName";
    static constexpr CE_String projectClassificationResultsDirectoryIdentifier = "classificationResultsDirName";
    static constexpr CE_String projectWorkingDirIdentifier = "workingDirName";

    //filetype the project file has
    static constexpr CE_String projectFileType = ".ini";

    //error messages for project names
    static constexpr CE_String ERROR_NOCHAR = "Name must contain at least 1 character";
    static constexpr CE_String ERROR_ONLY_SPACE = "Name should contain more than only space (\" \") characters";
    static constexpr CE_String ERROR_ILLEGAL_CHAR = "Name may not contain the  \"/\" or \"\\\" characters";
    static constexpr CE_String ERROR_DUPLICATE = "A project with this name already exists in the project directory";
    static constexpr CE_String ERROR_OS_SUPPORT = "The operating system cannot support this name";


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
