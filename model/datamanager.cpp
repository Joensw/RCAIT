#include "datamanager.h"

DataManager::DataManager(){
    mSettingsManager = new SettingsManager;
    mProjectManager = &ProjectManager::getInstance();
    mProjectManager->setProjectsDirectory(mSettingsManager->getProjectsDir());
    mModelManager = new ModelManager;
}
QStringList DataManager::getProjects(){
    return mProjectManager->getProjects();
}

void DataManager::createNewProject(QString projectName)
{
    mProjectManager->createNewProject(projectName);
}
bool DataManager::createNewProject(QString projectName, QString * error){
    return mProjectManager->createNewProject(projectName, error);
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
    mModelManager->createNewModel(this->getProjectsDir(), modelName, pluginName, baseModel);
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
void DataManager::saveProjectsDir(QString dir){
    mSettingsManager->saveProjectsDir(dir);
    mProjectManager->setProjectsDirectory(dir);
}
QString DataManager::getProjectsDir(){
    return mSettingsManager->getProjectsDir();
}
void DataManager::saveClassificationPluginDir(QString dir){
    mSettingsManager->saveClassificationPluginDir(dir);
}
QString DataManager::getClassificationPluginDir(){
    return mSettingsManager->getClassificationPluginDir();
}
void DataManager::saveImageLoaderPluginDir(QString dir){
    mSettingsManager->saveImageLoaderPluginDir(dir);
}
QString DataManager::getImageLoaderPluginDir(){
    return mSettingsManager->getImageLoaderPluginDir();
}

QStringList DataManager::getNamesOfSavedTrainingResults(){
    return mProjectManager->getNamesOfSavedTrainingResults();
}

QStringList DataManager::getImageLoaderPluginNames() {
    return mSettingsManager->getImageLoaderPluginNames();
}

bool DataManager::applyGlobalSettings(QString projectsDir, QString classificationPluginDir, QString imageLoaderPluginDir, QString *error, int *pathsChanged)
{
    if(mSettingsManager->applyGlobalSettings(projectsDir, classificationPluginDir, imageLoaderPluginDir, error, pathsChanged)){
            mProjectManager->setProjectsDirectory(getProjectsDir());
            return true;
    }
    return false;

}


