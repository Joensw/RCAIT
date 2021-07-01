#include "settingscontroller.h"


SettingsController::SettingsController(SettingsView *settingsView, QString *dataManager)
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

}

void SettingsController::slot_applyGlobalSettings(QString projectsDir, QString classificationPluginsDir, QString ImageLoaderPluginsDir)
{

}

