#ifndef PROJECTMANAGER_H
#define PROJECTMANAGER_H

#include <QString>
#include "classificationresult.h"
#include "trainingresult.h"
#include "classificationresult.h"


class ProjectManager {
public:
    //Threadsafe Singleton pattern
    ProjectManager(ProjectManager const &) = delete;

    void operator=(ProjectManager const &) = delete;

    static ProjectManager &getInstance() {
        static ProjectManager instance; // Guaranteed to be destroyed.
        // Instantiated on first use.
        return instance;
    }

    void createNewProject(QString projectName);

    void removeProject(QString projectName);

    void loadProject(QString projectName);

    QStringList getProjects();

    QString getProjectPath();

    QString getProjectTempDir();

    QString getProjectDataSetDir();

    QString getResultsDir();

    void saveClassificationResult(ClassificationResult result);

    void saveTrainingsResult(TrainingResult result);

    TrainingResult getTrainingsResult(QString modelResultName);

    QStringList getNamesOfSavedTrainingResults();

    void setProjectsDirectory(QString newDirectory);
signals:
    void sig_projectDirectoryChanged();
private:
    QString mProjectPath;
    QString mProjectTempDir;
    QString mProjectDataSetDir;
    QString mProjectResultsDir;
    QString mProjectName;

    QString mProjectsDirectory;

    ProjectManager();
};


#endif //PROJECTMANAGER_H
