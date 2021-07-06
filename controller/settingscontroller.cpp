#include "settingscontroller.h"


SettingsController::SettingsController(QObject *parent, DataManager *dataManager) : QObject(parent)
{
    this->mDataManager = dataManager;
}

void SettingsController::slot_openSettings()
{
    mSettingsView  = new SettingsView(nullptr, mDataManager->getPluginNames(), mDataManager->getPluginSettings());
    mSettingsView->show();
}

void SettingsController::slot_closeSettings()
{
    mSettingsView->close();
}

void SettingsController:: slot_applySettings(int index)
{
    mDataManager->savePluginSettings(index);
}

void SettingsController::slot_applyGlobalSettings(QString projectsDir, QString classificationPluginsDir, QString imageLoaderPluginsDir)
{
    mDataManager->saveProjectsDir(projectsDir);
    mDataManager->saveClassificationPluginDir(classificationPluginsDir);
    mDataManager->saveImageLoaderPluginDir(imageLoaderPluginsDir);
}

