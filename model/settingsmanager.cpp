#include "settingsmanager.h"


QString projectDirectoryIdentifier_settingsFile = "ProjectDirectory";
QString classificationPluginDirectoryIdentifier = "ClassificationPluginPath";
QString imageLoaderPluginDirectoryIdentifier = "ImageLoaderPluginPath";

SettingsManager::SettingsManager()
{
    mGlobalSettings = new QSettings();
    mClassificationPluginManager = ClassificationPluginManager::getInstance();
    mImageLoaderPluginManager = &ImageLoaderPluginManager::getInstance();

}
QStringList SettingsManager::getPluginNames(){
    QStringList loaderPlugins;
    QStringList classifierPlugins;
    loaderPlugins.append(classifierPlugins);
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
    QList<QWidget *> loaderPluginsWidgets;
    QList<QWidget *> classifierPluginsWidgets;
    loaderPluginsWidgets.append(classifierPluginsWidgets);
    return loaderPluginsWidgets;
}
void SettingsManager::savePluginSettings(int index){
    QStringList loaderPlugins;
    QStringList classifierPlugins;
    loaderPlugins.append(classifierPlugins);
    QString name = loaderPlugins.at(index);
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
