#include "settingsmanager.h"

SettingsManager::SettingsManager()
{

}


QStringList SettingsManager::getPluginNames(){
    QStringList q;
    return q;
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
