#include "settingsmanager.h"

SettingsManager::SettingsManager()
{

}
//gets names from ClassificationPluginManager and ImageLoaderPluginManager, combines them into one list
QStringList SettingsManager::getPluginNames(){
    QStringList loaderPlugins;
    QStringList classifierPlugins;
    loaderPlugins.append(classifierPlugins);
    return loaderPlugins;
}


QList<QWidget *> SettingsManager::getPluginSettings(){
    QList<QWidget *> q;
    return q;
}

void SettingsManager::savePluginSettings(int index){

}

void SettingsManager::saveProjectsDir(QString value){

}

QString SettingsManager::getProjectsDir(){
    QString q;
    return q;
}

void SettingsManager::saveClassificationPluginDir(QString value){

}
QString SettingsManager::getClassificationPluginDir(){
    QString q;
    return q;
}
void SettingsManager::saveImageLoaderPluginDir(QString value){

}
QString SettingsManager::getImageLoaderPluginDir(){
    QString q;
    return q;
}
