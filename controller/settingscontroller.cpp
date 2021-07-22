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
    mSettingsView->setCurrentProjectDirectory(mDataManager->getProjectsDir());
    mSettingsView->setCurrentClassificationPluginDirectory(mDataManager->getClassificationPluginDir());
    mSettingsView->setCurrentImageLoaderPluginDirectory(mDataManager->getImageLoaderPluginDir());
    mSettingsView->show();
}

void SettingsController:: slot_applySettings(int index)
{
    mDataManager->savePluginSettings(index);
}

void SettingsController::slot_applyGlobalSettings(QString projectsDir, QString classificationPluginsDir, QString imageLoaderPluginsDir)
{
    QString errorMessage;
    int sucessfulUpdates = 0;
    if (mDataManager->applyGlobalSettings(projectsDir, classificationPluginsDir, imageLoaderPluginsDir, &errorMessage, &sucessfulUpdates)){
        mSettingsView->setCurrentProjectDirectory(mDataManager->getProjectsDir());
        mSettingsView->setCurrentClassificationPluginDirectory(mDataManager->getClassificationPluginDir());
        mSettingsView->setCurrentImageLoaderPluginDirectory(mDataManager->getImageLoaderPluginDir());
        mSettingsView->pathsUpdated(sucessfulUpdates);
        mSettingsView->clearPaths();
        emit sig_projectDirectoryChanged();
        return;
    }
    mSettingsView->setGlobalSettingsError(errorMessage);
}


