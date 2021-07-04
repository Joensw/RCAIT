#include "settingscontroller.h"


SettingsController::SettingsController(SettingsView *settingsView, DataManager *dataManager)
{
    this->settingsView = settingsView;
    this->dataManager = dataManager;
}

void SettingsController::slot_openSettings()
{

}

void SettingsController::slot_closeSettings()
{

}

void SettingsController:: slot_applySettings(int index)
{
    dataManager->savePluginSettings(index);
}

void SettingsController::slot_applyGlobalSettings(QString projectsDir, QString classificationPluginsDir, QString imageLoaderPluginsDir)
{
    dataManager->saveProjectsDir(projectsDir);
    dataManager->saveClassificationPluginDir(classificationPluginsDir);
    dataManager->saveImageLoaderPluginDir(imageLoaderPluginsDir);
}

