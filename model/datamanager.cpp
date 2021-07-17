#include "datamanager.h"

DataManager::DataManager(){
    mSettingsManager = new SettingsManager;
    mProjectManager = &ProjectManager::getInstance();
    mProjectManager->setProjectsDirectory(mSettingsManager->getProjectsDir()); //could be put into constructor
    mModelManager = new ModelManager;
}
QStringList DataManager::getProjects(){
    return mProjectManager->getProjects();
}
void DataManager::createNewProject(QString projectName){
    mProjectManager->createNewProject(projectName);
}

void DataManager::removeProject(QString projectName){
    mProjectManager->removeProject(projectName);
}

void DataManager::loadProject(QString projectName){
    mProjectManager->loadProject(projectName);
}

QString DataManager::getProjectPath(){
    return mProjectManager->getProjectPath();
}

QString DataManager::getProjectTempDir(){
    return mProjectManager->getProjectTempDir();
}

QString DataManager::getProjectDataSetDir(){
    return mProjectManager->getProjectDataSetDir();
}

bool DataManager::verifyDirectories()
{
    return mSettingsManager->verifyDirectories();
}

bool DataManager::verifyPaths(QString projectsDirectory, QString classificationPluginDirectory, QString imageLoaderDirectory)
{
    return mSettingsManager->verifyPaths(projectsDirectory, classificationPluginDirectory, imageLoaderDirectory);
}

bool DataManager::verifyPath(QString path)
{
    return mSettingsManager->verifyPath(path);
}

void DataManager::createNewModel(QString modelName, QString pluginName, QString baseModel){
    mModelManager->createNewModel(modelName, pluginName, baseModel);
}
void DataManager::removeModel(QString modelName, QString pluginName){
    mModelManager->removeModel(modelName, pluginName);
}
void DataManager::loadModel(QString modelName, QString pluginName){
    mModelManager->loadModel(modelName, pluginName);
}
QString DataManager::getCurrentModel(){
    return mModelManager->getCurrentModel();
}
QString DataManager::getCurrentClassificationPlugin(){
    return mModelManager->getCurrentPlugin();
}



QStringList DataManager::getPluginNames(){
    return mSettingsManager->getPluginNames();
}
QStringList DataManager::getClassificationPluginNames(){
    return mSettingsManager->getClassificationPluginNames();
}
QStringList DataManager::getPluginBases(QString plugin)
{
    return mSettingsManager->getClassificationPluginBase(plugin);
}


QList<QWidget*> DataManager::getPluginSettings(){
    return mSettingsManager->getPluginSettings();
}
void DataManager::savePluginSettings(int index){
    mSettingsManager->savePluginSettings(index);
}
void DataManager::saveProjectsDir(QString value){
    mSettingsManager->saveProjectsDir(value);
    mProjectManager->setProjectsDirectory(value);
}
QString DataManager::getProjectsDir(){
    return mSettingsManager->getProjectsDir();
}
void DataManager::saveClassificationPluginDir(QString value){
    mSettingsManager->saveClassificationPluginDir(value);
}
QString DataManager::getClassificationPluginDir(){
    return mSettingsManager->getClassificationPluginDir();
}
void DataManager::saveImageLoaderPluginDir(QString value){
    mSettingsManager->saveImageLoaderPluginDir(value);
}
QString DataManager::getImageLoaderPluginDir(){
    return mSettingsManager->getImageLoaderPluginDir();
}

void DataManager::saveClassificationResult(ClassificationResult result){
    mProjectManager->saveClassificationResult(result);
}
void DataManager::saveTrainingsResult(ClassificationResult result){
    return mProjectManager->saveTrainingsResult(result);
}
TrainingResult DataManager::getTrainingsResult(QString modelResultName){
    return mProjectManager->getTrainingsResult(modelResultName);
}
QStringList DataManager::getNamesOfSavedTrainingResults(){
    return mProjectManager->getNamesOfSavedTrainingResults();
}


