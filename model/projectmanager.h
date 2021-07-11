#ifndef PROJECTMANAGER_H
#define PROJECTMANAGER_H

#include <QString>
#include "classificationresult.h"
#include "trainingresult.h"
#include "classificationresult.h"


class ProjectManager {
public:
    ProjectManager();

    void createNewProject(QString projectName);

    void removeProject(QString projectName);

    void loadProject(QString projectName);

    QStringList getProjects();

    QString getProjectPath();

    QString getProjectTempDir();

    QString getProjectDataSetDir();

    QString getResultsDir();

    void saveClassificationResult(ClassificationResult result);

    void saveTrainingsResult(ClassificationResult result);

    TrainingResult getTrainingsResult(QString modelResultName);

    QStringList getNamesOfSavedTrainingResults();


private:
    QString mProjectPath;
    QString mProjectTempDir;
    QString mProjectDataSetDir;
    QString mProjectResultsDir;
    QString mProjectName;
};


#endif //PROJECTMANAGER_H
