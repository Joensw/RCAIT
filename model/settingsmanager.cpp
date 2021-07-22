#include "settingsmanager.h"


QString projectDirectoryIdentifier_settingsFile = "ProjectDirectory";
QString classificationPluginDirectoryIdentifier = "ClassificationPluginPath";
QString imageLoaderPluginDirectoryIdentifier = "ImageLoaderPluginPath";

SettingsManager::SettingsManager()
{
    mGlobalSettings = new QSettings();
    mClassificationPluginManager = &ClassificationPluginManager::getInstance();
    mImageLoaderPluginManager = &ImageLoaderPluginManager::getInstance();
    mImageLoaderPluginManager->loadPlugins(getImageLoaderPluginDir());

}
QStringList SettingsManager::getPluginNames(){
    QStringList loaderPlugins = mImageLoaderPluginManager->getNamesOfPlugins();
    QStringList classifierPlugins;
    //loaderPlugins.append(classifierPlugins);
    return loaderPlugins;
}

QStringList SettingsManager::getClassificationPluginNames(){
    QStringList classifierPlugins;
    return classifierPlugins;
}

QStringList SettingsManager::getClassificationPluginBase(QString plugin)
{
    return mClassificationPluginManager->getClassificationPluginBases(plugin);
}

bool SettingsManager::verifyDirectories()
{
    if (mGlobalSettings->contains(projectDirectoryIdentifier_settingsFile)
            && mGlobalSettings->contains(classificationPluginDirectoryIdentifier)
            && mGlobalSettings->contains(imageLoaderPluginDirectoryIdentifier)) {
        //all keys exist and have values

        //extract values
        QString projectPath = mGlobalSettings->value(projectDirectoryIdentifier_settingsFile).toString();
        QString classificationPath = mGlobalSettings->value(classificationPluginDirectoryIdentifier).toString();
        QString imageLoaderPath = mGlobalSettings->value(imageLoaderPluginDirectoryIdentifier).toString();

        return verifyPaths(projectPath, classificationPath, imageLoaderPath);
    }
    return false; //settings file wasnt complete
}

bool SettingsManager::verifyPaths(QString projectsDirectory, QString classificationPluginDirectory, QString imageLoaderDirectory)
{
    if (projectsDirectory == classificationPluginDirectory ||
            projectsDirectory == imageLoaderDirectory ||
            classificationPluginDirectory == imageLoaderDirectory) {
        return false;
    }

    //this is necessary, QDir treats the "" directory as "." and will always return true on .exists();
    if (projectsDirectory.isEmpty() || classificationPluginDirectory.isEmpty() || imageLoaderDirectory.isEmpty()){
        return false;
    }

    //make dirs from the values, check if they exist
    //if they dont they the programm cannot operate
    QDir projectDir = QDir(projectsDirectory);
    QDir classificationDir = QDir(classificationPluginDirectory);
    QDir imageLoaderDir = QDir(imageLoaderDirectory);

    if (projectDir.exists() && classificationDir.exists() && imageLoaderDir.exists()) {
        return  true;
    }
    return false; //one of the specified paths couldnt be found
}

bool SettingsManager::verifyPath(QString path)
{
    if (path.isEmpty()){ // null and empty string are not valid paths
        return false;
    }
    QDir directory = QDir(path);

    if (directory.exists()){
        return true;
    }
    return false;
}

QList<QWidget *> SettingsManager::getPluginSettings(){
    QList<QWidget *> loaderPluginsWidgets = mImageLoaderPluginManager->getConfigurationWidgets();
    QList<QWidget *> classifierPluginsWidgets;
    loaderPluginsWidgets.append(classifierPluginsWidgets);
    return loaderPluginsWidgets;
}
void SettingsManager::savePluginSettings(int index){
    QStringList loaderPlugins = mImageLoaderPluginManager->getNamesOfPlugins();
    QStringList classifierPlugins;
    loaderPlugins.append(classifierPlugins);
    QString name = loaderPlugins.at(index);
    mImageLoaderPluginManager->saveConfiguration(name);
    //ToDo: Wenn Klassifikationspluginmanager verwendet wird kurz checken bei wem das Plugin ist
    //mClassificationPluginManager.saveConfiguration(name)
}

void SettingsManager::saveProjectsDir(QString value){
    mGlobalSettings->setValue(projectDirectoryIdentifier_settingsFile, value);
}

QString SettingsManager::getProjectsDir(){
    return mGlobalSettings->value(projectDirectoryIdentifier_settingsFile).toString();
}

void SettingsManager::saveClassificationPluginDir(QString value){
    mGlobalSettings->setValue(classificationPluginDirectoryIdentifier, value);
}
QString SettingsManager::getClassificationPluginDir(){
    return mGlobalSettings->value(classificationPluginDirectoryIdentifier).toString();
}
void SettingsManager::saveImageLoaderPluginDir(QString value){
    mGlobalSettings->setValue(imageLoaderPluginDirectoryIdentifier, value);
}
QString SettingsManager::getImageLoaderPluginDir(){
    return mGlobalSettings->value(imageLoaderPluginDirectoryIdentifier).toString();
}

bool SettingsManager::applyGlobalSettings(QString projectsDir, QString classificationPluginDir, QString imageLoaderPluginDir,
                                          QString *error, int * pathsChanged){

    int pathsChangedTemp = 0;
    QString tempProjectsDir = getProjectsDir();
    QString tempClassificationPluginDir = getClassificationPluginDir();
    QString tempImageLoaderPluginDir = getImageLoaderPluginDir();


    //Check if there is an actual update to any of the paths
    if (!projectsDir.isEmpty()) {
        pathsChangedTemp++;
        tempProjectsDir = projectsDir;
    }
    if (!classificationPluginDir.isEmpty()) {
        pathsChangedTemp++;
        tempClassificationPluginDir = classificationPluginDir;
    }
    if (!imageLoaderPluginDir.isEmpty()) {
        pathsChangedTemp++;
        tempImageLoaderPluginDir = imageLoaderPluginDir;
    }

    //check if all paths are allowed and if any of them are overlapping
    if (verifyPaths(tempProjectsDir, tempClassificationPluginDir, tempImageLoaderPluginDir)){
        saveProjectsDir(tempProjectsDir);
        saveClassificationPluginDir(tempClassificationPluginDir);
        saveImageLoaderPluginDir(tempImageLoaderPluginDir);

        if (pathsChanged != nullptr){
            *pathsChanged = pathsChangedTemp;
        }

        return true;

    }
    if (error != nullptr){
        *error = "Settings have not been updated, there is a conflict.\n"
             "paths may not be identical and must exist, this includes new and unchanged paths";
    }
    if (pathsChanged != nullptr){
        *pathsChanged = 0;
    }
    return false;
}

QStringList SettingsManager::getImageLoaderPluginNames() {
    return mImageLoaderPluginManager->getNamesOfPlugins();
}
