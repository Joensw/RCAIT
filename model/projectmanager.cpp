#include "projectmanager.h"
#include "confusionmatrix.h"
#include "accuracycurve.h"

#include <QDir>
#include <QSettings>
#include <QRegularExpression>

const QString resultsDirectoryName = "results";
const QString datasetDirectoryName = "data";
const QString tempDirectoryName = "temp";
const QString trainingsResultsDirectoryName = "training_results";
const QString classificationResultsDirectoryName = "classification_results";

const QString projectNameIdentifier = "projectName";
const QString projectDatasetDirectoryIdentifier = "datasetDirName";
const QString projectTempDirectoryIdentifier = "tempDirName";
const QString projectResultsDirectoryIdentifier = "resultsDirName";
const QString projectTrainingsResultsDirectoryIdentifer = "trainingResultsDirName";
const QString projectClassificationResultsDirectoryIdentifier = "classificationResultsDirName";

//on creation, meaning program startup, there will be no project selected. all the strings will be null/empty
ProjectManager::ProjectManager() {

}

void ProjectManager::createNewProject(QString projectName)
{
    QString newProjectPath = mProjectsDirectory + "/" + projectName + "/" + projectName + ".ini";

    /*goes into the projects folder, then into the specific project folder
    * there it creates a new ini file, which can be seen as the "project file"
    */

    //non existing folders / directories will be automatically created
    QSettings newProjectfile(newProjectPath, QSettings::IniFormat);

    //this is only to get an absolute path, without .. and .
    QDir projectDir(QFileInfo(newProjectPath).absoluteDir());

    QString absolute = projectDir.absolutePath();

    newProjectfile.setValue(projectNameIdentifier, projectName);
    newProjectfile.setValue(projectDatasetDirectoryIdentifier, datasetDirectoryName);
    newProjectfile.setValue(projectTempDirectoryIdentifier, tempDirectoryName);

    newProjectfile.setValue(projectResultsDirectoryIdentifier, resultsDirectoryName);
    newProjectfile.setValue(projectTrainingsResultsDirectoryIdentifer, trainingsResultsDirectoryName);
    newProjectfile.setValue(projectClassificationResultsDirectoryIdentifier, classificationResultsDirectoryName);

    //make temp, results and data subdirectories
    QDir dir;
    dir.mkpath(absolute + "/" +  datasetDirectoryName);
    dir.mkpath(absolute + "/" + tempDirectoryName);
    dir.mkpath(absolute + "/" +  resultsDirectoryName);

    //make subdirectories for results

    dir.mkpath(absolute + "/" +  resultsDirectoryName + "/" + trainingsResultsDirectoryName);
    dir.mkpath(absolute + "/" +  resultsDirectoryName + "/" + classificationResultsDirectoryName);
}

QStringList ProjectManager::getProjects() {
    if (!mProjectsDirectory.isEmpty()){
        QDir projectsDir(mProjectsDirectory);
        projectsDir.setFilter(QDir::AllDirs | QDir::NoDotAndDotDot);
        return projectsDir.entryList();
    }
    QStringList empty;
    return empty;
}

bool ProjectManager::createNewProject(QString projectName, QString * error) {
    if (!verifyName(projectName, error)){
        return false;
    }
    createNewProject(projectName);
    return true;
}

void ProjectManager::removeProject(QString projectName) {
    QDir targetDir(mProjectsDirectory + "/" + projectName);
    targetDir.removeRecursively();
}

void ProjectManager::loadProject(QString projectName) {
    QString loadProjectPath = mProjectsDirectory + "/" + projectName + "/" + projectName + ".ini";

    QSettings projectfile(loadProjectPath, QSettings::IniFormat);

    mProjectName = projectfile.value(projectNameIdentifier).toString();
    mProjectPath = mProjectsDirectory + "/" + projectName;
    mProjectDataSetDir = mProjectPath + "/" + projectfile.value(projectDatasetDirectoryIdentifier).toString();
    mProjectTempDir = mProjectPath + "/" + projectfile.value(projectTempDirectoryIdentifier).toString();
    mProjectResultsDir = mProjectPath + "/" + projectfile.value(projectResultsDirectoryIdentifier).toString();
    mProjectTrainingResultsDir =  mProjectResultsDir + "/" + projectfile.value(projectTrainingsResultsDirectoryIdentifer).toString();
    mProjectClassificationResultsDir = mProjectResultsDir + "/" + projectfile.value(projectClassificationResultsDirectoryIdentifier).toString();
}
QString ProjectManager::getProjectPath() {
    return mProjectPath;
}

QString ProjectManager::getProjectTempDir() {
    return mProjectTempDir;
}

QString ProjectManager::getProjectDataSetDir() {
    return mProjectDataSetDir;
}

QString ProjectManager::getResultsDir() {
    return mProjectResultsDir;
}

QString ProjectManager::getTrainingResultsDir()
{
    return mProjectTrainingResultsDir;
}

QString ProjectManager::getClassificationResultsDir()
{
    return mProjectClassificationResultsDir;
}

QStringList ProjectManager::getNamesOfSavedTrainingResults() {
    if (mProjectPath.isEmpty()) {
        qDebug() << "should not have been called yet, no project has been opened";
    }
    if (!mProjectPath.isEmpty()){
        QDir trainingResultsDir(getTrainingResultsDir());

        QStringList filters;
        filters << "*.txt";
        trainingResultsDir.setNameFilters(filters);

        trainingResultsDir.setFilter(QDir::Files | QDir::NoDotAndDotDot);

        QFileInfoList filelist = trainingResultsDir.entryInfoList();
        QStringList fileNameList;
        for(const QFileInfo &f: filelist){
            fileNameList.append(f.baseName());
        }
        return fileNameList ;
    }
    QStringList empty;
    return empty;
}

void ProjectManager::setProjectsDirectory(QString newDirectory)
{
    mProjectsDirectory = newDirectory;
}

bool ProjectManager::verifyName(QString projectName, QString *error)
{
    if (projectName.length() == 0){
        error->append(QObject::tr("Name must contain at least 1 character") + "\n");
        return false;
    }


    QRegularExpression noSpacesEx("^[ ]+$");
    QRegularExpressionMatch match = noSpacesEx.match(projectName);
    if (match.hasMatch()){
        error->append(QObject::tr("Name should contain more than only space (\" \") characters"));
        return false;
    }

    //the next step is easier if we filters these outs prematurely
    if (projectName.contains("/") || projectName.contains("\\")) {
        error->append(QObject::tr("Name may not contain the  \"/\" or \"\\\" characters") + "\n");
        return false;
    }


    //check if name is already taken
    QDir projectsDir(mProjectsDirectory);
    projectsDir.setFilter(QDir::AllDirs | QDir::NoDotAndDotDot);
    QStringList projects = projectsDir.entryList();
    if (projects.contains(projectName)) {
        error->append(QObject::tr("A project with this name aleady exists in the project directory"));
        return false;

    }

    //check if folders with this name can simply not be created
    QDir tempDir(mProjectsDirectory + "/" + projectName);
    tempDir.setFilter(QDir::NoDotAndDotDot);
    if (!tempDir.mkpath(mProjectsDirectory + "/" + projectName )){
        error->append(QObject::tr("The Operating system cannot support this name"));
        return false;
    }
    tempDir.removeRecursively();



    return true;
}



