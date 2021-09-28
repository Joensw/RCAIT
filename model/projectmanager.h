/**
 * @file projectmanager.h
 *
 * @brief functions for managing project directories on disk
 *
 * @author Jonas Wille
 */
#ifndef PROJECTMANAGER_H
#define PROJECTMANAGER_H

#include <QString>
#include <QStringBuilder>
#include <QObject>
#include <QStringList>
#include <QDir>
#include <QSettings>
#include <QRegularExpression>

/**
 * @brief The ProjectManager class contains the logic for manipulating the projects of the application
 */
class ProjectManager : public QObject {
Q_OBJECT
public:

    /**
     * @brief ProjectManager deleted copy constructor
     */

    ProjectManager(ProjectManager const &) = delete;

    /**
     * @brief operator = deleted assingment operator
     */

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
    bool createNewProject(const QString &projectName, QString *error);

    /**
     * @brief removeProject deleted the project sub directory from the current projects directory.
     * @param projectName name of the project
     */
    void removeProject(const QString &projectName);

    /**
     * @brief loadProject loads the information of a project with a given name into the class so it can be accessed later.
     * @param projectName name of the project
     * @return true if it could be loaded, false otherwise
     */
    bool loadProject(const QString &projectName);

    /**
     * @return list of all directories in the projects directory
     */
    [[nodiscard]] QStringList getProjects();

    /**
     * @brief getProjectPath will return null string if no project is opened
     * @return absolute path to the currently opened project's subdirectory
     */
    [[nodiscard]] QString getProjectPath();

    /**
     * @brief getProjectName will return null string if no project is opened
     * @return name of the currently opened project
     */
    [[nodiscard]] QString getProjectName();

    /**
     * @brief getProjectDataSetDir will return null string if no project is opened
     * @return absoulute path to the data set directory of the currently opened project
     */
    [[nodiscard]] QString getProjectDataSetDir();

    /**
     * @return the absolute path to the validation images subfolder of the data set
     */
    [[nodiscard]] QString getProjectDataSetValSubdir();

    /**
     * @return the absolute path to the training images subfolder of the data set
     */

    [[nodiscard]] QString getProjectDataSetTrainSubdir();


    /**
     * @brief getProjectImageTempDir will return null string if no project is opened
     * @return the absolute path to the image temporary directory of the current project
     */

    [[nodiscard]] QString getProjectImageTempDir();

    /**
     * @brief getProjectAugTempDir will return null string if no project is opened
     * @return the absolute path to the data augmentation temporary directory of the current project
     */

    [[nodiscard]] QString getProjectAugTempDir();

    /**
     * @brief getResultsDir will return null string if no project is opened
     * @return absolute path to the results directroy of the currently opened project
     */
    [[nodiscard]] QString getResultsDir();

    /**
     * @brief getTrainingResultsDir will return null string if no project is opened
     * @return  absolute path to the trainings results subdirectory of the currently opened project
     */
    [[nodiscard]] QString getTrainingResultsDir();

    /**
     * @brief getClassificationResultsDir will return null string if no project is opened
     * @return absolute path to the classification results subdirectory of the currently opened project
     */
    [[nodiscard]] QString getClassificationResultsDir();

    /** Only .txt files are returned and within the list they have no file ending, if no project is opened an empty list is returned
     * @return getNamesOfSavedTrainingResults returns the names of all the files in the trainings results folder
     */
    [[nodiscard]] QStringList getNamesOfSavedTrainingResults();

    /**
     * The names receive the suffix _1, if this name is already taken, the suffix is incremented till it is available
     * @brief createWorkDirSubfolder creates a new subfolder in the working directory
     * @param name string argument, name of the folder
     * @return absolute path to the folder
     */
    [[nodiscard]] QString createWorkDirSubfolder(const QString &name);

    /**
     * @brief setProjectsDirectory sets the  projects directory, ie. the directory projects are to be created, deleted and loaded from
     * @param newDirectory the new projects directory
     */
    void setProjectsDirectory(const QString &newDirectory);

private:
    //Names of the subfolders in the project directory
    //These can be changed.
    //Make sure to choose names that are not disallowed in windows ar under linux!
    static constexpr auto resultsDirectoryName = "results";
    static constexpr auto datasetDirectoryName = "data";
    static constexpr auto tempImagesDirectoryName = "temp_Images";
    static constexpr auto tempDataAugDirectoryName = "temp_Aug";
    static constexpr auto trainingsResultsDirectoryName = "training_results";
    static constexpr auto classificationResultsDirectoryName = "classification_results";
    static constexpr auto validiationDatasetDirectoryName = "validation";
    static constexpr auto trainingDatasetDirectoryName = "training";
    static constexpr auto workingDirectoryName = "working_directory";

    //keys of the <String, String> pair in the project file
    static constexpr auto projectNameIdentifier = "projectName";
    static constexpr auto projectDatasetDirectoryIdentifier = "datasetDirName";
    static constexpr auto projectValidationDatasetIdentifier = "validationDatasetDirName";
    static constexpr auto projectTrainingDatasetIdentifier = "trainingDatasetDirName";
    static constexpr auto projectTempImagesDirectoryIdentifier = "tempImagesDirName";
    static constexpr auto projectTempDataAugDirectoryIdentifier = "tempDataAugDirName";
    static constexpr auto projectResultsDirectoryIdentifier = "resultsDirName";
    static constexpr auto projectTrainingsResultsDirectoryIdentifer = "trainingResultsDirName";
    static constexpr auto projectClassificationResultsDirectoryIdentifier = "classificationResultsDirName";
    static constexpr auto projectWorkingDirIdentifier = "workingDirName";

    //filetype the project file has
    static constexpr auto projectFileType = ".ini";

    //error messages for project names
    static constexpr auto ERROR_NOCHAR = QT_TR_NOOP("Name must contain at least 1 character");
    static constexpr auto ERROR_ONLY_SPACE = QT_TR_NOOP("Name should contain more than only space (\" \") characters");
    static constexpr auto ERROR_ILLEGAL_CHAR = QT_TR_NOOP("Name may not contain the  \"/\" or \"\\\" characters");
    static constexpr auto ERROR_DUPLICATE = QT_TR_NOOP( "A project with this name already exists in the project directory");
    static constexpr auto ERROR_OS_SUPPORT = QT_TR_NOOP("The operating system cannot support this name");

    //Regex to match String with consisting of only spaces
    static constexpr auto REGEX_ONLY_SPACE = "^[ ]+$";

    static constexpr auto TEXT_FILE_FILTER = "*.txt";

    static const QVector<QString> UNWANTED_NAME_SEQUENCES;

    bool verifyName(QString projectName, QString *error);

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
