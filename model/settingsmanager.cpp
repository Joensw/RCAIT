#include "settingsmanager.h"

const QString GLOBAL_SETTINGS_LOCATION = "../settings.ini";
QString projectDirectoryIdentifier = "ProjectDirectory";
QString classificationPluginDirectoryIdentifier = "ClassificationPluginPath";
QString imageLoaderPluginDirectoryIdentifier = "ImageLoaderPluginPath";

SettingsManager::SettingsManager()
{
    QSettings globalSettings = QSettings(GLOBAL_SETTINGS_LOCATION, QSettings::IniFormat);
    globalSettings.value("test", "zwecke");
}
//gets names from ClassificationPluginManager and ImageLoaderPluginManager, combines them into one list
QStringList SettingsManager::getPluginNames(){
    QStringList loaderPlugins;
    QStringList classifierPlugins;
    loaderPlugins.append(classifierPlugins);
    return loaderPlugins;
}
//sends a request to both pluginManagers, combines them into a single list and returns them
QList<QWidget *> SettingsManager::getPluginSettings(){
    QList<QWidget *> loaderPluginsWidgets;
    QList<QWidget *> classifierPluginsWidgets;
    loaderPluginsWidgets.append(classifierPluginsWidgets);
    return loaderPluginsWidgets;
}
//Idee: baue namens liste nochmal auf, hol das element mit dem entsprechenden index
void SettingsManager::savePluginSettings(int index){
    //this maybe isnt the best solution here
    QStringList loaderPlugins;
    QStringList classifierPlugins;
    loaderPlugins.append(classifierPlugins);
    QString name = loaderPlugins.at(index);
    //classificationPluginManager.saveConfiguration(name)
}

void SettingsManager::saveProjectsDir(QString value){
    mGlobalSettings.setValue(projectDirectoryIdentifier, value);
}

QString SettingsManager::getProjectsDir(){
    return mGlobalSettings.value(projectDirectoryIdentifier).toString();
}

void SettingsManager::saveClassificationPluginDir(QString value){
    mGlobalSettings.setValue(classificationPluginDirectoryIdentifier, value);
}
QString SettingsManager::getClassificationPluginDir(){
    return mGlobalSettings.value(classificationPluginDirectoryIdentifier).toString();
}
void SettingsManager::saveImageLoaderPluginDir(QString value){
    mGlobalSettings.setValue(projectDirectoryIdentifier, value);
}
QString SettingsManager::getImageLoaderPluginDir(){
    return mGlobalSettings.value(projectDirectoryIdentifier).toString();
}
