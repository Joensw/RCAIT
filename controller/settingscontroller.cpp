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
    mSettingsView->setCurrentProjectDirectory(mDataManager->getProjectsDir());
    mSettingsView->setCurrentClassificationPluginDirectory(mDataManager->getClassificationPluginDir());
    mSettingsView->setCurrentImageLoaderPluginDirectory(mDataManager->getImageLoaderPluginDir());
}

void SettingsController:: slot_applySettings(int index)
{
    mDataManager->savePluginSettings(index);
}

void SettingsController::slot_applyGlobalSettings(QString projectDir, QString classificationPluginDir, QString imageLoaderPluginDir)
{
    QString errorMessage;
    int sucessfulUpdates = 0;
    if (mDataManager->applyGlobalSettings(projectDir, classificationPluginDir, imageLoaderPluginDir, &errorMessage, &sucessfulUpdates)){
        mSettingsView->setCurrentProjectDirectory(mDataManager->getProjectsDir());
        mSettingsView->setCurrentClassificationPluginDirectory(mDataManager->getClassificationPluginDir());
        mSettingsView->setCurrentImageLoaderPluginDirectory(mDataManager->getImageLoaderPluginDir());
        mSettingsView->pathsUpdated(sucessfulUpdates);
        mSettingsView->clearPaths();
        emit sig_projectDirectoryChanged(mDataManager->getProjectsDir());
        emit sig_imagePluginsDirectoryChanged(mDataManager->getImageLoaderPluginDir());
        mSettingsView->addPluginWidgets(mDataManager->getPluginNames(), mDataManager->getPluginSettings());
        return;
    }
    mSettingsView->setGlobalSettingsError(errorMessage);
}


