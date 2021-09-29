/**
 * @file datamanager.cpp
 *
 * @brief fuctions for managing a classification dataset on disk
 *
 * @author various
 */
#include "datamanager.h"

#include <utility>

DataManager::DataManager()
        : mSettingsManager(&SettingsManager::getInstance()),
          mProjectManager(&ProjectManager::getInstance()),
          mModelManager(&ModelManager::getInstance()),
          mConfigurationManager(&ConfigurationManager::getInstance()) {

    mProjectManager->setProjectsDirectory(mConfigurationManager->getProjectsDir());
}

QStringList DataManager::getProjects() {
    return mProjectManager->getProjects();
}

void DataManager::createNewProject(QString projectName) {
    mProjectManager->createNewProject(std::move(projectName));
}

bool DataManager::createNewProject(const QString& projectName, QString *error) {
    return mProjectManager->createNewProject(projectName, error);
}

void DataManager::removeProject(const QString& projectName) {
    mProjectManager->removeProject(projectName);
    mModelManager->removeAllModelsOfProject(projectName);
}

bool DataManager::loadProject(const QString& projectName) {
    return mProjectManager->loadProject(projectName);
}

QString DataManager::getProjectPath() {
    return mProjectManager->getProjectPath();
}

QString DataManager::getProjectDataSetDir() {

    return mProjectManager->getProjectDataSetDir();
}

QString DataManager::getProjectName() {
    return mProjectManager->getProjectName();
}

QString DataManager::getProjectAugTempDir() {
    return mProjectManager->getProjectAugTempDir();
}

QString DataManager::getProjectImageTempDir() {
    return mProjectManager->getProjectImageTempDir();
}

QString DataManager::createNewWorkSubDir(const QString &name) {
    return mProjectManager->createWorkDirSubfolder(name);
}

QString DataManager::getProjectDataSetValSubdir() {
    return mProjectManager->getProjectDataSetValSubdir();
}

QString DataManager::getProjectDataSetTrainSubdir() {
    return mProjectManager->getProjectDataSetTrainSubdir();
}

bool DataManager::verifyDirectories() {
    return mConfigurationManager->verifyDirectories();
}

bool DataManager::verifyPaths(const QStringList& paths) {
    return ConfigurationManager::verifyPaths(paths);
}

void DataManager::createNewModel(QString modelName, QString pluginName, QString baseModel) {
    mModelManager->createNewModel(getProjectName(), std::move(modelName), std::move(pluginName), std::move(baseModel));
}

void DataManager::removeModel(QString modelName) {
    mModelManager->removeModel(getProjectName(), std::move(modelName));
}

void DataManager::loadModel(QString modelName, QString pluginName) {
    mModelManager->loadModel(std::move(modelName), std::move(pluginName));
}

QStringList DataManager::getModelNamesOfCurrentProject() {
    return mModelManager->getModelNamesOfProject(getProjectName());
}

QString DataManager::getCurrentModel() {
    return mModelManager->getCurrentModel();
}

void DataManager::saveLastWorkingDirectoryOfModel(const QString& projectName, const QString& modelName, const QString& workingDirectory) {
    mModelManager->saveLastWorkingDirectoryOfModel(projectName, modelName, workingDirectory);
}

QString DataManager::recallLastWorkingDirectoryOfModel(QString projectName, QString modelName) {
    return mModelManager->recallLastWorkingDirectoryOfModel(std::move(projectName), std::move(modelName));
}

QString DataManager::recallPluginNameOfModel(QString projectName, QString modelName) {
    return mModelManager->recallPluginNameOfModell(std::move(projectName), std::move(modelName));
}

QString DataManager::getCurrentClassificationPlugin() {
    return mModelManager->getCurrentPlugin();
}


QStringList DataManager::getPluginNames() {
    return mSettingsManager->getPluginNames();
}

QStringList DataManager::getClassificationPluginNames() {
    return mSettingsManager->getClassificationPluginNames();
}

QStringList DataManager::getPluginBases(const QString& plugin) {
    return mSettingsManager->getClassificationPluginBase(plugin);
}


QList<QSharedPointer<QWidget>> DataManager::getPluginSettings() {
    return mSettingsManager->getPluginSettings();
}

QList<QSharedPointer<QIcon>> DataManager::getPluginIcons() {
    return mSettingsManager->getPluginIcons();
}

void DataManager::savePluginSettings(int index) {
    mSettingsManager->savePluginSettings(index);
}

void DataManager::saveProjectsDir(const QString& dir) {
    mConfigurationManager->saveProjectsDir(dir);
    mProjectManager->setProjectsDirectory(dir);
}

QString DataManager::getProjectsDir() {
    return mConfigurationManager->getProjectsDir();
}

void DataManager::saveClassificationPluginDir(const QString& dir) {
    mSettingsManager->saveClassificationPluginDir(dir);
}

QString DataManager::getClassificationPluginDir() {
    return mConfigurationManager->getClassificationPluginDir();
}

void DataManager::saveImageLoaderPluginDir(const QString& dir) {
    mSettingsManager->saveImageLoaderPluginDir(dir);
}

QString DataManager::getImageLoaderPluginDir() {
    return mConfigurationManager->getImageLoaderPluginDir();
}

QString DataManager::getPythonExecutablePath() {
    return mConfigurationManager->getPythonExecutablePath();
}

QStringList DataManager::getNamesOfSavedTrainingResults() {
    return mProjectManager->getNamesOfSavedTrainingResults();
}

QSharedPointer<QWidget> DataManager::getInputWidget() {
    return mModelManager->getInputWidget();
}

QSharedPointer<QWidget> DataManager::getDataAugmentationInputWidget() {
    return mModelManager->getDataAugmentationInputWidget();
}

QStringList DataManager::getImageLoaderPluginNames() {
    return mSettingsManager->getImageLoaderPluginNames();
}


bool
DataManager::applyGlobalSettings(const QString &projectsDir, const QString &classificationPluginDir, const QString &imageLoaderPluginDir,
                                 const QString &pythonPath, QString &error, int &pathsChanged) {
    if (mSettingsManager->applyGlobalSettings(projectsDir, classificationPluginDir, imageLoaderPluginDir, pythonPath, error,
                                              pathsChanged)) {
        mProjectManager->setProjectsDirectory(getProjectsDir());
        return true;
    }
    return false;

}


