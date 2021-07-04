#include "settingsmanager.h"

const QString GLOBAL_SETTINGS_LOCATION = "../settings.ini";
QString projectDirectoryIdentifier = "ProjectDirectory";
QString classificationPluginDirectoryIdentifier = "ClassificationPluginPath";
QString imageLoaderPluginDirectoryIdentifier = "ImageLoaderPluginPath";

SettingsManager::SettingsManager()
{
    QSettings globalSettings = QSettings(GLOBAL_SETTINGS_LOCATION, QSettings::IniFormat);
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
//Nur mit einem int hier etwas abzuspeichern wird eventuell schwierig
void SettingsManager::savePluginSettings(int index){

}

void SettingsManager::saveProjectsDir(QString value){
    globalSettings.setValue(projectDirectoryIdentifier, value);
}

QString SettingsManager::getProjectsDir(){
    return globalSettings.value(projectDirectoryIdentifier).toString();
}

void SettingsManager::saveClassificationPluginDir(QString value){
    globalSettings.setValue(classificationPluginDirectoryIdentifier, value);
}
QString SettingsManager::getClassificationPluginDir(){
    return globalSettings.value(classificationPluginDirectoryIdentifier).toString();
}
void SettingsManager::saveImageLoaderPluginDir(QString value){
    globalSettings.setValue(projectDirectoryIdentifier, value);
}
QString SettingsManager::getImageLoaderPluginDir(){
    return globalSettings.value(projectDirectoryIdentifier).toString();
}
