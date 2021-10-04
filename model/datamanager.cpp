/**
 * @file datamanager.cpp
 *
 * @brief functions for managing a classification dataset on disk
 *
 * @author various
 */
#include "datamanager.h"

DataManager::DataManager()
        : mProjectManager(&ProjectManager::getInstance()),
          mModelManager(&ModelManager::getInstance()),
          mSettingsManager(&SettingsManager::getInstance()),
          mConfigurationManager(&ConfigurationManager::getInstance()) {

    mProjectManager->setProjectsDirectory(mConfigurationManager->getProjectsDir());
}

[[maybe_unused]] QStringList DataManager::getProjects() {
    return mProjectManager->getProjects();
}

void DataManager::createNewProject(const QString &projectName) {
    mProjectManager->createNewProject(projectName);
}

bool DataManager::createNewProject(const QString& projectName, QString &error) {
    return mProjectManager->createNewProject(projectName, error);
}

void DataManager::removeProject(const QString& projectName) {
    mProjectManager->removeProject(projectName);
    mModelManager->removeAllModelsOfProject(projectName);
}

bool DataManager::loadProject(const QString& projectName) {
    return mProjectManager->loadProject(projectName);
}

[[maybe_unused]] QString DataManager::getProjectPath() {
    return mProjectManager->getProjectPath();
}

[[maybe_unused]] QString DataManager::getProjectDataSetDir() {

    return mProjectManager->getProjectDataSetDir();
}

[[maybe_unused]] QString DataManager::getProjectName() {
    return mProjectManager->getProjectName();
}

[[maybe_unused]] QString DataManager::getProjectAugTempDir() {
    return mProjectManager->getProjectAugTempDir();
}

[[maybe_unused]] QString DataManager::getProjectImageTempDir() {
    return mProjectManager->getProjectImageTempDir();
}

QString DataManager::createNewWorkSubDir(const QString &name) {
    return mProjectManager->createWorkDirSubfolder(name);
}

[[maybe_unused]]QString DataManager::getProjectDataSetValSubdir() {
    return mProjectManager->getProjectDataSetValSubdir();
}

[[maybe_unused]]QString DataManager::getProjectDataSetTrainSubdir() {
    return mProjectManager->getProjectDataSetTrainSubdir();
}

[[maybe_unused]] bool DataManager::verifyDirectories() {
    return mConfigurationManager->verifyDirectories();
}

[[maybe_unused]] bool DataManager::verifyPaths(const QStringList &paths) {
    return ConfigurationManager::verifyPaths(paths);
}

bool DataManager::createNewModel(const QString &modelName, const QString &pluginName, const QString &baseModel) {
    return mModelManager->createNewModel(getProjectName(), modelName, pluginName, baseModel);
}

bool DataManager::removeModel(const QString &modelName) {
    return mModelManager->removeModel(getProjectName(), modelName);
}

void DataManager::loadModel(const QString &modelName, const QString &pluginName) {
    mModelManager->loadModel(modelName, pluginName);
}

[[maybe_unused]] QStringList DataManager::getModelNamesOfCurrentProject() {
    return mModelManager->getModelNamesOfProject(getProjectName());
}

[[maybe_unused]] QString DataManager::getCurrentModel() {
    return mModelManager->getCurrentModel();
}

void DataManager::saveLastWorkingDirectoryOfModel(const QString& projectName, const QString& modelName, const QString& workingDirectory) {
    mModelManager->saveLastWorkingDirectoryOfModel(projectName, modelName, workingDirectory);
}

QString DataManager::recallLastWorkingDirectoryOfModel(const QString &projectName, const QString &modelName) {
    return mModelManager->recallLastWorkingDirectoryOfModel(projectName, modelName);
}

QString DataManager::recallPluginNameOfModel(const QString &projectName, const QString &modelName) {
    return mModelManager->recallPluginNameOfModel(projectName, modelName);
}

[[maybe_unused]] QString DataManager::getCurrentClassificationPlugin() {
    return mModelManager->getCurrentPlugin();
}


[[maybe_unused]] QStringList DataManager::getPluginNames() {
    return mSettingsManager->getPluginNames();
}

[[maybe_unused]] QStringList DataManager::getClassificationPluginNames() {
    return mSettingsManager->getClassificationPluginNames();
}

[[maybe_unused]] QStringList DataManager::getPluginBases(const QString &plugin) {
    return mSettingsManager->getClassificationPluginBase(plugin);
}

[[maybe_unused]] QList <QSharedPointer<QWidget>> DataManager::getPluginSettings() {
    return mSettingsManager->getPluginSettings();
}

[[maybe_unused]] QList <QSharedPointer<QIcon>> DataManager::getPluginIcons() const {
    return mSettingsManager->getPluginIcons();
}

void DataManager::savePluginSettings(const int &index) {
    mSettingsManager->savePluginSettings(index);
}

void DataManager::saveProjectsDir(const QString& dir) {
    mConfigurationManager->saveProjectsDir(dir);
    mProjectManager->setProjectsDirectory(dir);
}

[[maybe_unused]] QString DataManager::getProjectsDir() const {
    return mConfigurationManager->getProjectsDir();
}

void DataManager::saveClassificationPluginDir(const QString& dir) {
    mSettingsManager->saveClassificationPluginDir(dir);
}

[[maybe_unused]] QString DataManager::getClassificationPluginDir() const {
    return mConfigurationManager->getClassificationPluginDir();
}

void DataManager::saveImageLoaderPluginDir(const QString& dir) {
    mSettingsManager->saveImageLoaderPluginDir(dir);
}

[[maybe_unused]] QString DataManager::getImageLoaderPluginDir() const {
    return mConfigurationManager->getImageLoaderPluginDir();
}

[[maybe_unused]] QString DataManager::getPythonExecutablePath() const {
    return mConfigurationManager->getPythonExecutablePath();
}

[[maybe_unused]] QStringList DataManager::getNamesOfSavedTrainingResults() const {
    return mProjectManager->getNamesOfSavedTrainingResults();
}

[[maybe_unused]] QSharedPointer <QWidget> DataManager::getInputWidget() const {
    return mModelManager->getInputWidget();
}

[[maybe_unused]] QSharedPointer <QWidget> DataManager::getDataAugmentationInputWidget() const {
    return mModelManager->getDataAugmentationInputWidget();
}

[[maybe_unused]] QStringList DataManager::getImageLoaderPluginNames() const {
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


