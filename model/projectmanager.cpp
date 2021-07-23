#include "projectmanager.h"
#include "confusionmatrix.h"
#include "losscurve.h"

#include <QDir>
#include <QSettings>
#include <QRegularExpression>


//names of the subfolders in the project directory
//These can be changed, however projects based on the old naming scheme become unreadable
QString resultsDirectoryName = "results";
QString datasetDirectoryName = "data";
QString tempDirectoryName = "temp";
QString trainingsResultsDirectoryName = "training_results";
QString classificationResultsDirectoryName = "classification_results";

//keys of the <String, String> pair in the project file
QString projectNameIdentifier = "projectName";
QString projectDirectoryIdentifier_projectsFile = "projectDir";
QString projectDatasetDirectoryIdentifier = "datasetDirName";
QString projectTempDirectoryIdentifier = "tempDirName";

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
    //newProjectfile.setValue(projectDirectoryIdentifier_projectsFile, absolute);
    newProjectfile.setValue(projectDatasetDirectoryIdentifier, datasetDirectoryName);
    newProjectfile.setValue(projectTempDirectoryIdentifier, tempDirectoryName);

    //make temp, results and Data subdirectories
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
    //mProjectPath = projectfile.value(projectDirectoryIdentifier_projectsFile).toString();
    mProjectDataSetDir = mProjectPath + "/" + projectfile.value(projectDatasetDirectoryIdentifier).toString();
    mProjectTempDir = mProjectPath + "/" + projectfile.value(projectTempDirectoryIdentifier).toString();
    mProjectResultsDir = mProjectPath + "/" + resultsDirectoryName;

    qDebug() << getNamesOfSavedTrainingResults();
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
/* Currently this is not readable by a human because it is in binary format.
 * the information is recoverable by opening a datastream to the file and reading the contents in
 * order they were entered and then building a new ClassificationResult object from this.
 * ie out << map << list1 << list2 is read with in >> map >> list 1 >> list
 */
void ProjectManager::saveClassificationResult(ClassificationResult result) {
    QFile file(mProjectResultsDir + "/" + result.generateIdentifier());

    if (!file.open(QIODevice::WriteOnly)){
        qDebug() << "Could not save classification results";
        return;
    }

    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_6_1);

    out << result.getClassificationData() << result.getLabels() << result.getAdditionalResults();

    file.flush();
    file.close();
}

void ProjectManager::saveTrainingsResult(TrainingResult result) {
    QFile file(mProjectResultsDir + "/" + result.generateIdentifier());

    if (!file.open(QIODevice::WriteOnly)){
        qDebug() << "Could not save training results";
        return;
    }

    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_6_1);

    ConfusionMatrix * cmTemp = result.getConfusionMatrix();
    LossCurve * lcTemp = result.getLossCurve();

    QString identifierCM = cmTemp->getIdentifier();
    QStringList classLabels = cmTemp->getClassLabels();
    QList<int> values= cmTemp->getValues();

    QMap<int, QPair<double, double>> data = lcTemp->getData();
    QString identiferLC = lcTemp->getIdentifier();

    QList<QImage> additionalResults = result.getAdditionalResults();

    out << result.getTop1Accuracy() << result.getTop5Accuracy() << result.getMostMisclassifiedImages()
        << identifierCM << classLabels << values << data << identiferLC << additionalResults;

    file.flush();
    file.close();
}

TrainingResult ProjectManager::getTrainingsResult(QString modelResultName) {
    QFile file(mProjectResultsDir + "/" + modelResultName);

    if (!file.open(QIODevice::WriteOnly)){
        qDebug() << "Could not open training results";
        //return;
    }

    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_6_1);

    QString identifierCM;
    QStringList classLabels;
    QList<int> values;

    QMap<int, QPair<double, double>> data;
    QString identiferLC;

    double top1Acc;
    double top5Acc;
    QList<QImage> mostMisclassifiedImages;

    QList<QImage> additionalResults;

    in >> top1Acc >> top5Acc >> mostMisclassifiedImages >> identifierCM >> classLabels >> values >> data >> identiferLC >> additionalResults;

    //reconstruct Confusion matrix
    ConfusionMatrix * confMatrix = new ConfusionMatrix(identifierCM, classLabels, values);
    //QSharedPointer<ConfusionMatrix> confMatrix = QSharedPointer<ConfusionMatrix>(new ConfusionMatrix(identifierCM, classLabels, values));
    //reconstruct loss curve
    LossCurve * lossCurve = new LossCurve(identiferLC, data);
    //QSharedPointer<LossCurve> lossCurve = QSharedPointer<LossCurve>(new LossCurve(identiferLC, data));
    //reconstruct training result
    TrainingResult constructedTR(lossCurve, confMatrix, mostMisclassifiedImages, top1Acc, top5Acc, additionalResults);

    file.close();

    return constructedTR;
}

QStringList ProjectManager::getNamesOfSavedTrainingResults() {
    if (mProjectPath.isEmpty()) {
        qDebug() << "should not have been called yet, no project has been opened";
    }
    QString trainingResults = mProjectPath + "/" + resultsDirectoryName + "/" + trainingsResultsDirectoryName;
    if (!mProjectPath.isEmpty()){
        QDir trainingResultsDir(trainingResults);

        QStringList filters;
        filters << "*.txt";
        trainingResultsDir.setNameFilters(filters);

        trainingResultsDir.setFilter(QDir::Files | QDir::NoDotAndDotDot);

        QFileInfoList filelist = trainingResultsDir.entryInfoList();
        QStringList fileNameList;
        for(QFileInfo f: filelist){
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

bool ProjectManager::verifyName(QString input, QString *error)
{
    bool status = true;
    if (input.length() == 0){
        error->append(QObject::tr("Name must contain at least 1 character") +"\n");
        status = false;
    }

    //check if name comtains special characters
    QRegularExpression rx1("^[\\w]*$");
    QRegularExpressionMatch match = rx1.match(input);
    if (!match.hasMatch()) {
        error->append(QObject::tr("Name may not contain special characters") + "\n");
        status = false;
    }

    //check if name is already taken
    QDir projectsDir(mProjectsDirectory);
    projectsDir.setFilter(QDir::AllDirs | QDir::NoDotAndDotDot);
    QStringList projects = projectsDir.entryList();
    if (projects.contains(input)) {
        error->append(QObject::tr("A project with this name aleady exists in the project directory"));
        status = false;

    }
    return status;
}



