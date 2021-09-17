#include "projectmanager.h"

const QVector<QString> ProjectManager::UNWANTED_NAME_SEQUENCES = {"/", "\\"};

ProjectManager::ProjectManager() {

}

void ProjectManager::createNewProject(QString projectName)
{
    QString newProjectPath = mProjectsDirectory % "/" % projectName % "/" % projectName % projectFileType;

    /*goes into the projects folder, then into the specific project folder
    * there it creates a new ini file, which can be seen as the "project file"
    */

    //non existing folders / directories will be automatically created
    QSettings newProjectfile(newProjectPath, QSettings::IniFormat);

    //this is only to get an absolute path, without .. and .
    QDir projectDir(QFileInfo(newProjectPath).absoluteDir());

    QString absolute = projectDir.absolutePath();

    newProjectfile.setValue(projectNameIdentifier, projectName);

    newProjectfile.setValue(projectTempImagesDirectoryIdentifier, tempImagesDirectoryName);
    newProjectfile.setValue(projectTempDataAugDirectoryIdentifier, tempDataAugDirectoryName);

    newProjectfile.setValue(projectDatasetDirectoryIdentifier, datasetDirectoryName);
    newProjectfile.setValue(projectValidationDatasetIdentifier, validiationDatasetDirectoryName);
    newProjectfile.setValue(projectTrainingDatasetIdentifier, trainingDatasetDirectoryName);

    newProjectfile.setValue(projectResultsDirectoryIdentifier, resultsDirectoryName);
    newProjectfile.setValue(projectTrainingsResultsDirectoryIdentifer, trainingsResultsDirectoryName);
    newProjectfile.setValue(projectClassificationResultsDirectoryIdentifier, classificationResultsDirectoryName);

    newProjectfile.setValue(projectWorkingDirIdentifier, workingDirectoryName);

    //make temp, results and data subdirectories
    QDir dir;
    dir.mkpath(absolute %  "/" %  datasetDirectoryName);
    dir.mkpath(absolute % "/" % tempImagesDirectoryName);
    dir.mkpath(absolute % "/" % tempDataAugDirectoryName);
    dir.mkpath(absolute % "/" %  resultsDirectoryName);
    dir.mkpath(absolute % "/" % workingDirectoryName);

    //make subdirectories for results
    dir.mkpath(absolute % "/" %  resultsDirectoryName % "/" % trainingsResultsDirectoryName);
    dir.mkpath(absolute % "/" %  resultsDirectoryName % "/" % classificationResultsDirectoryName);

    //make subdirectories for dataset

    dir.mkpath(absolute % "/" % datasetDirectoryName % "/" % validiationDatasetDirectoryName);
    dir.mkpath(absolute % "/" % datasetDirectoryName % "/" % trainingDatasetDirectoryName);
}

QStringList ProjectManager::getProjects() {
    if (!mProjectsDirectory.isEmpty()){
        QDir projectsDir(mProjectsDirectory);
        projectsDir.setFilter(QDir::AllDirs | QDir::NoDotAndDotDot);
        return projectsDir.entryList();
    }
    return {};
}

bool ProjectManager::createNewProject(const QString &projectName, QString * error) {
    if (!verifyName(projectName, error)){
        return false;
    }
    createNewProject(projectName);
    return true;
}

void ProjectManager::removeProject(const QString &projectName) {
    QDir targetDir(mProjectsDirectory % "/" % projectName);
    targetDir.removeRecursively();
}

void ProjectManager::loadProject(const QString &projectName) {
    QString loadProjectPath = mProjectsDirectory % "/" % projectName % "/" % projectName % projectFileType;

    QSettings projectfile(loadProjectPath, QSettings::IniFormat);

    mProjectName = projectfile.value(projectNameIdentifier).toString();
    mProjectPath = mProjectsDirectory % "/" % projectName;
    mProjectDataSetDir = mProjectPath % "/" % projectfile.value(projectDatasetDirectoryIdentifier).toString();
    mProjectDataSetValSubdir =  mProjectDataSetDir % "/" % projectfile.value(projectValidationDatasetIdentifier).toString();
    mProjectDataSetTrainSubdir = mProjectDataSetDir % "/" % projectfile.value(projectTrainingDatasetIdentifier).toString();

    mProjectImagesTempDir = mProjectPath % "/" % projectfile.value(projectTempImagesDirectoryIdentifier).toString();
    mProjectAugTempDir = mProjectPath % "/" % projectfile.value(projectTempDataAugDirectoryIdentifier).toString();

    mProjectResultsDir = mProjectPath % "/" % projectfile.value(projectResultsDirectoryIdentifier).toString();
    mProjectTrainingResultsDir =  mProjectResultsDir % "/" % projectfile.value(projectTrainingsResultsDirectoryIdentifer).toString();
    mProjectClassificationResultsDir = mProjectResultsDir % "/" % projectfile.value(projectClassificationResultsDirectoryIdentifier).toString();

    mProjectWorkingDir = mProjectPath % "/" % projectfile.value(projectWorkingDirIdentifier).toString();

    /*
    qDebug() << mProjectName;
    qDebug() << mProjectPath;
    qDebug() << mProjectDataSetDir;
    qDebug() << mProjectDataSetValSubdir;
    qDebug() << mProjectDataSetTrainSubdir;
    qDebug() << mProjectImagesTempDir;
    qDebug() << mProjectAugTempDir;
    qDebug() << mProjectResultsDir;
    qDebug() << mProjectTrainingResultsDir;
    qDebug() << mProjectClassificationResultsDir;
    qDebug() << mProjectWorkingDir;
    */

}
QString ProjectManager::getProjectPath() {
    return mProjectPath;
}

QString ProjectManager::getProjectName() {
    return mProjectName;
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

QString ProjectManager::getProjectDataSetValSubdir(){
    return mProjectDataSetValSubdir;
}

QString ProjectManager::getProjectDataSetTrainSubdir(){
    return mProjectDataSetTrainSubdir;
}

QString ProjectManager::getProjectImageTempDir() {
    return mProjectImagesTempDir;
}

QString ProjectManager::getProjectAugTempDir(){
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

QString ProjectManager::createWorkDirSubfolder(const QString &name){
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

bool ProjectManager::verifyName(QString projectName, QString *error)
{
    if (projectName.length() == 0){
        error->append(ERROR_NOCHAR);
        return false;
    }

    static QRegularExpression noSpacesEx(REGEX_ONLY_SPACE);
    QRegularExpressionMatch match = noSpacesEx.match(projectName);
    if (match.hasMatch()) {
        error->append(ERROR_ONLY_SPACE);
        return false;
    }
    for (const QString &charSequence: UNWANTED_NAME_SEQUENCES) {
        if (projectName.contains(charSequence)) {
            error->append(ERROR_ILLEGAL_CHAR);
            return false;
        }
    }
    /*
    if (projectName.contains("/") || projectName.contains("\\")) {
        error->append(ERROR_ILLEGAL_CHAR);
        return false;
    }
    */
    //check if name is already taken
    QDir projectsDir(mProjectsDirectory);
    projectsDir.setFilter(QDir::AllDirs | QDir::NoDotAndDotDot);
    QStringList projects = projectsDir.entryList();
    if (projects.contains(projectName)) {
        error->append(ERROR_DUPLICATE);
        return false;

    }

    //check if folders with this name can simply not be created
    QDir tempDir(mProjectsDirectory % "/" % projectName);
    tempDir.setFilter(QDir::NoDotAndDotDot);
    if (!tempDir.mkpath(mProjectsDirectory % "/" % projectName )){
        error->append(ERROR_OS_SUPPORT);
        return false;
    }
    tempDir.removeRecursively();



    return true;
}



