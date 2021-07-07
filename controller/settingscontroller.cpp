#include "settingscontroller.h"


SettingsController::SettingsController(QObject *parent, DataManager *dataManager) : QObject(parent)
{
    this->mDataManager = dataManager;
    mSettingsView  = new SettingsView(nullptr, mDataManager->getPluginNames(), mDataManager->getPluginSettings());
    connect(mSettingsView, &SettingsView::sig_applyGlobalSettings, this, &SettingsController::slot_applyGlobalSettings);
    connect(mSettingsView, &SettingsView::sig_applySettings, this, &SettingsController::slot_applySettings);

}

void SettingsController::slot_openSettings()
{
    mSettingsView->show();
}

//void SettingsController::slot_closeSettings()
//{
//    mSettingsView->close();
//}

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

