/**
 * @file projectmanager.cpp
 *
 * @brief functions for managing project directories on disk
 *
 * @author Jonas Wille
 */
#include "projectmanager.h"


ProjectManager::ProjectManager() = default;

void ProjectManager::createNewProject(const QString &projectName) const {
    QString newProjectPath = mProjectsDirectory % "/" % projectName % "/" % projectName % projectFileType;

    /*goes into the projects' folder, then into the specific project folder
    * there it creates a new ini file, which can be seen as the "project file"
    */

    //non-existing folders / directories will be automatically created
    QSettings newProjectfile(newProjectPath, QSettings::IniFormat);

    //this is only to get an absolute path, without .. and .
    QDir projectDir(QFileInfo(newProjectPath).absoluteDir());

    QString absolute = projectDir.absolutePath();

    newProjectfile.setValue(projectNameIdentifier, projectName);

    newProjectfile.setValue(projectTempImagesDirectoryIdentifier, tempImagesDirectoryName);
    newProjectfile.setValue(projectTempDataAugDirectoryIdentifier, tempDataAugDirectoryName);

    newProjectfile.setValue(projectDatasetDirectoryIdentifier, datasetDirectoryName);
    newProjectfile.setValue(projectValidationDatasetIdentifier, validationDatasetDirectoryName);
    newProjectfile.setValue(projectTrainingDatasetIdentifier, trainingDatasetDirectoryName);

    newProjectfile.setValue(projectResultsDirectoryIdentifier, resultsDirectoryName);
    newProjectfile.setValue(projectTrainingsResultsDirectoryIdentifier, trainingsResultsDirectoryName);
    newProjectfile.setValue(projectClassificationResultsDirectoryIdentifier, classificationResultsDirectoryName);

    newProjectfile.setValue(projectWorkingDirIdentifier, workingDirectoryName);

    //make temp, results and data subdirectories
    QDir dir;
    dir.mkpath(absolute % "/" %  datasetDirectoryName);
    dir.mkpath(absolute % "/" % tempImagesDirectoryName);
    dir.mkpath(absolute % "/" % tempDataAugDirectoryName);
    dir.mkpath(absolute % "/" %  resultsDirectoryName);
    dir.mkpath(absolute % "/" % workingDirectoryName);

    //make subdirectories for results
    dir.mkpath(absolute % "/" %  resultsDirectoryName % "/" % trainingsResultsDirectoryName);
    dir.mkpath(absolute % "/" %  resultsDirectoryName % "/" % classificationResultsDirectoryName);

    //make subdirectories for dataset

    dir.mkpath(absolute % "/" % datasetDirectoryName % "/" % validationDatasetDirectoryName);
    dir.mkpath(absolute % "/" % datasetDirectoryName % "/" % trainingDatasetDirectoryName);
}

QStringList ProjectManager::getProjects() const {
    if (!mProjectsDirectory.isEmpty()) {
        QDir projectsDir(mProjectsDirectory);
        projectsDir.setFilter(QDir::AllDirs | QDir::NoDotAndDotDot);
        return projectsDir.entryList();
    }
    return {};
}

bool ProjectManager::createNewProject(const QString &projectName, QString &error) {
    if (!verifyName(projectName, error)){
        return false;
    }
    createNewProject(projectName);
    return true;
}

void ProjectManager::removeProject(const QString &projectName) const {
    QDir targetDir(mProjectsDirectory % "/" % projectName);
    targetDir.removeRecursively();
}

bool ProjectManager::loadProject(const QString &projectName) {
    QString loadProjectPath = mProjectsDirectory % "/" % projectName % "/" % projectName % projectFileType;

    QSettings projectfile(loadProjectPath, QSettings::IniFormat);

    //check if the file exists / and is configured properly
    QStringList keys = {projectNameIdentifier, projectDatasetDirectoryIdentifier, projectValidationDatasetIdentifier,
                        projectTrainingDatasetIdentifier,
                        projectTempImagesDirectoryIdentifier, projectTempDataAugDirectoryIdentifier,
                        projectResultsDirectoryIdentifier,
                        projectTrainingsResultsDirectoryIdentifier, projectClassificationResultsDirectoryIdentifier,
                        projectWorkingDirIdentifier};

    auto allKeys = projectfile.allKeys();
    for (const QString &key: keys) {
        if (!allKeys.contains(key)) {
            return false;
        }
    }


    mProjectName = projectfile.value(projectNameIdentifier).toString();
    mProjectPath = mProjectsDirectory % "/" % projectName;
    mProjectDataSetDir = mProjectPath % "/" % projectfile.value(projectDatasetDirectoryIdentifier).toString();
    mProjectDataSetValSubdir =
            mProjectDataSetDir % "/" % projectfile.value(projectValidationDatasetIdentifier).toString();
    mProjectDataSetTrainSubdir =
            mProjectDataSetDir % "/" % projectfile.value(projectTrainingDatasetIdentifier).toString();

    mProjectImagesTempDir = mProjectPath % "/" % projectfile.value(projectTempImagesDirectoryIdentifier).toString();
    mProjectAugTempDir = mProjectPath % "/" % projectfile.value(projectTempDataAugDirectoryIdentifier).toString();

    mProjectResultsDir = mProjectPath % "/" % projectfile.value(projectResultsDirectoryIdentifier).toString();
    mProjectTrainingResultsDir =
            mProjectResultsDir % "/" % projectfile.value(projectTrainingsResultsDirectoryIdentifier).toString();
    mProjectClassificationResultsDir =
            mProjectResultsDir % "/" % projectfile.value(projectClassificationResultsDirectoryIdentifier).toString();

    mProjectWorkingDir = mProjectPath % "/" % projectfile.value(projectWorkingDirIdentifier).toString();
    return true;


}

QString ProjectManager::getProjectPath() const {
    return mProjectPath;
}

QString ProjectManager::getProjectName() const {
    return mProjectName;
}

QString ProjectManager::getProjectDataSetDir() const {
    return mProjectDataSetDir;
}

QString ProjectManager::getResultsDir() const {
    return mProjectResultsDir;
}

QString ProjectManager::getTrainingResultsDir() const {
    return mProjectTrainingResultsDir;
}

QString ProjectManager::getClassificationResultsDir() const {
    return mProjectClassificationResultsDir;
}

QString ProjectManager::getProjectDataSetValSubdir() const {
    return mProjectDataSetValSubdir;
}

QString ProjectManager::getProjectDataSetTrainSubdir() const {
    return mProjectDataSetTrainSubdir;
}

QString ProjectManager::getProjectImageTempDir() const {
    return mProjectImagesTempDir;
}

QString ProjectManager::getProjectAugTempDir() const {
    return mProjectAugTempDir;
}

QStringList ProjectManager::getNamesOfSavedTrainingResults() {
    if (mProjectPath.isEmpty()) {
        qDebug() << "should not have been called yet, no project has been opened";
    }
    if (!mProjectPath.isEmpty()){
        QDir trainingResultsDir(getTrainingResultsDir());

        trainingResultsDir.setNameFilters({TEXT_FILE_FILTER});

        trainingResultsDir.setFilter(QDir::Files | QDir::NoDotAndDotDot);

        QFileInfoList filelist = trainingResultsDir.entryInfoList();
        QStringList fileNameList;
        for(const QFileInfo &f: filelist){
            fileNameList.append(f.baseName());
        }
        return fileNameList;
    }
    return {};
}

QString ProjectManager::createWorkDirSubfolder(const QString &name) const {
    int runningNameCount = 1;
    QDir dir(mProjectWorkingDir);
    dir.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
    QString alteredName = name % "_" % QString::number(runningNameCount);
    QStringList entries = dir.entryList();

    while (entries.contains(alteredName)) {
        runningNameCount++;
        alteredName = name % "_" % QString::number(runningNameCount);
    }
    QString path = mProjectWorkingDir % "/" % alteredName;
    dir.mkpath(path);
    return path;
}

void ProjectManager::setProjectsDirectory(const QString &newDirectory)
{
    mProjectsDirectory = newDirectory;
}

bool ProjectManager::verifyName(const QString &projectName, QString &error) const {
    if (projectName.length() == 0) {
        error = ERROR_NOCHAR;
        return false;
    }

    static QRegularExpression noSpacesEx(REGEX_ONLY_SPACE);
    QRegularExpressionMatch match = noSpacesEx.match(projectName);
    if (match.hasMatch()) {
        error = ERROR_ONLY_SPACE;
        return false;
    }
    for (const QString &charSequence: UNWANTED_NAME_SEQUENCES) {
        if (projectName.contains(charSequence)) {
            error = ERROR_ILLEGAL_CHAR;
            return false;
        }
    }
    //check if name is already taken
    QDir projectsDir(mProjectsDirectory);
    projectsDir.setFilter(QDir::AllDirs | QDir::NoDotAndDotDot);
    if (projectsDir.entryList().contains(projectName)) {
        error = ERROR_DUPLICATE;
        return false;
    }

    //check if folders with this name can simply not be created
    QDir tempDir(mProjectsDirectory % "/" % projectName);
    tempDir.setFilter(QDir::NoDotAndDotDot);
    if (!tempDir.mkpath(mProjectsDirectory % "/" % projectName )){
        error = ERROR_OS_SUPPORT;
        return false;
    }
    tempDir.removeRecursively();



    return true;
}



