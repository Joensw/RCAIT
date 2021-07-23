#ifndef PROJECTMANAGER_H
#define PROJECTMANAGER_H

#include <QString>
#include <QObject>
#include "classificationresult.h"
#include "trainingresult.h"
#include "classificationresult.h"

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
     * @return
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
     * @return list of all directories in the projects directory
     */
    QStringList getProjects();

    /**
     * @brief getProjectPath will return null string if no project is opened
     * @return absolute path to the currently opened project's subdirectory
     */
    QString getProjectPath();

    /**
     * @brief getProjectTempDir will return null string if no project is opened
     * @return absolute path to the temporary directory of the currently opened project
     */
    QString getProjectTempDir();

    /**
     * @brief getProjectDataSetDir will return null string if no project is opened
     * @return absoulute path to the data set directory of the currently opened project
     */
    QString getProjectDataSetDir();

    /**
     * @brief getResultsDir will return null string if no project is opened
     * @return absolute path to the results directroy of the currently opened project
     */
    QString getResultsDir();

    /** Serialises the object in a binary format, it is not readable to a human.
     *  The object is saved to the classifcation result sub directory
     * @brief saveClassificationResult serialises and saves a classification results object
     * @param result
     */
    void saveClassificationResult(ClassificationResult result);

    /** Serialises the object in a binary format, it is not readable to a human.
     *  The object is saved to the training result sub directory
     * @brief saveTrainingsResult serialises and saves a training result object.
     * @param result
     */
    void saveTrainingsResult(TrainingResult result);

    /**
     * @brief getTrainingsResult rebuilds a TrainingResult object
     * @param modelResultName name of the file the object is to be built from
     * @return the rebuilt object
     */
    TrainingResult getTrainingsResult(QString modelResultName);

    /** Only .txt files are returns and within the list they have no file ending
     * @brief getNamesOfSavedTrainingResults returns the names of all the files in the trainings results folder
     * @return
     */
    QStringList getNamesOfSavedTrainingResults();

    /**
     * @brief setProjectsDirectory sets the  projects directory, ie. the directory projects are to be created, deleted and loaded from
     * @param newDirectory the new projects directory
     */
    void setProjectsDirectory(QString newDirectory);

private:
    bool verifyName(QString input, QString * error);

    QString mProjectPath;
    QString mProjectTempDir;
    QString mProjectDataSetDir;
    QString mProjectResultsDir;
    QString mProjectName;

    QString mProjectsDirectory;

    ProjectManager();
};


#endif //PROJECTMANAGER_H
