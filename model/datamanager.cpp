/**
 * @file datamanager.cpp
 *
 * @brief fuctions for managing a classification dataset on disk
 *
 * @author various
 */
#include "datamanager.h"

DataManager::DataManager()
        : mSettingsManager(&SettingsManager::getInstance()),
          mProjectManager(&ProjectManager::getInstance()),
          mModelManager(&ModelManager::getInstance()) {

    mProjectManager->setProjectsDirectory(mSettingsManager->getProjectsDir());
}

QStringList DataManager::getProjects() {
    return mProjectManager->getProjects();
}

void DataManager::createNewProject(QString projectName) {
    mProjectManager->createNewProject(projectName);
}

bool DataManager::createNewProject(QString projectName, QString *error) {
    return mProjectManager->createNewProject(projectName, error);
}

void DataManager::removeProject(QString projectName) {
    mProjectManager->removeProject(projectName);
    mModelManager->removeAllModelsOfProject(projectName);
}

void DataManager::loadProject(QString projectName) {
    mProjectManager->loadProject(projectName);
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
    return mSettingsManager->verifyDirectories();
}

bool DataManager::verifyPaths(QString projectsDirectory, QString classificationPluginDirectory,
                              QString imageLoaderDirectory) {
    return mSettingsManager->verifyPaths(projectsDirectory, classificationPluginDirectory, imageLoaderDirectory);
}

bool DataManager::verifyPath(QString path) {
    return mSettingsManager->verifyPath(path);
}

void DataManager::createNewModel(QString modelName, QString pluginName, QString baseModel) {
    mModelManager->createNewModel(getProjectName(), modelName, pluginName, baseModel);
}

void DataManager::removeModel(QString modelName) {
    mModelManager->removeModel(getProjectName(), modelName);
}

void DataManager::loadModel(QString modelName, QString pluginName) {
    mModelManager->loadModel(modelName, pluginName);
}

QStringList DataManager::getModelNamesOfCurrentProject() {
    return mModelManager->getModelNamesOfProject(getProjectName());
}

QString DataManager::getCurrentModel() {
    return mModelManager->getCurrentModel();
}

void DataManager::saveLastWorkingDirectoryOfModel(QString projectName, QString modelName, QString workingDirectory) {
    mModelManager->saveLastWorkingDirectoryOfModel(projectName, modelName, workingDirectory);
}

QString DataManager::recallLastWorkingDirectoryOfModel(QString projectName, QString modelName) {
    return mModelManager->recallLastWorkingDirectoryOfModel(projectName, modelName);
}

QString DataManager::recallPluginNameOfModell(QString projectName, QString modelName) {
    return mModelManager->recallPluginNameOfModell(projectName, modelName);
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

QStringList DataManager::getPluginBases(QString plugin) {
    return mSettingsManager->getClassificationPluginBase(plugin);
}


QList<QWidget *> DataManager::getPluginSettings() {
    return mSettingsManager->getPluginSettings();
}

void DataManager::savePluginSettings(int index) {
    mSettingsManager->savePluginSettings(index);
}

void DataManager::saveProjectsDir(QString dir) {
    mSettingsManager->saveProjectsDir(dir);
    mProjectManager->setProjectsDirectory(dir);
}

QString DataManager::getProjectsDir() {
    return mSettingsManager->getProjectsDir();
}

void DataManager::saveClassificationPluginDir(QString dir) {
    mSettingsManager->saveClassificationPluginDir(dir);
}

QString DataManager::getClassificationPluginDir() {
    return mSettingsManager->getClassificationPluginDir();
}

void DataManager::saveImageLoaderPluginDir(QString dir) {
    mSettingsManager->saveImageLoaderPluginDir(dir);
}

QString DataManager::getImageLoaderPluginDir() {
    return mSettingsManager->getImageLoaderPluginDir();
}

QStringList DataManager::getNamesOfSavedTrainingResults() {
    return mProjectManager->getNamesOfSavedTrainingResults();
}

QWidget *DataManager::getInputWidget() {
    return mModelManager->getInputWidget();
}

QWidget *DataManager::getDataAugmentationInputWidget() {
    return mModelManager->getDataAugmentationInputWidget();
}

QStringList DataManager::getImageLoaderPluginNames() {
    return mSettingsManager->getImageLoaderPluginNames();
}


bool
DataManager::applyGlobalSettings(QString projectsDir, QString classificationPluginDir, QString imageLoaderPluginDir,
                                 QString *error, int *pathsChanged) {
    if (mSettingsManager->applyGlobalSettings(projectsDir, classificationPluginDir, imageLoaderPluginDir, error,
                                              pathsChanged)) {
        mProjectManager->setProjectsDirectory(getProjectsDir());
        return true;
    }
    return false;

}


