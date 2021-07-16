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

void SettingsController:: slot_applySettings(int index)
{
    mDataManager->savePluginSettings(index);
}

void SettingsController::slot_applyGlobalSettings(QString projectsDir, QString classificationPluginsDir, QString imageLoaderPluginsDir)
{
    char sucessfulUpdates = 0;
    /*
    if(mDataManager->verifyPaths(projectsDir, classificationPluginsDir, imageLoaderPluginsDir)){
        //empty paths will not be verified, null string will also not be verfied
        mDataManager->saveProjectsDir(projectsDir);
        mDataManager->saveClassificationPluginDir(classificationPluginsDir);
        mDataManager->saveImageLoaderPluginDir(imageLoaderPluginsDir);
    }
    */

    if (mDataManager->verifyPath(projectsDir)) {
        mDataManager->saveProjectsDir(projectsDir);
        sucessfulUpdates++;
    }
    if (mDataManager->verifyPath(classificationPluginsDir)) {
        mDataManager->saveClassificationPluginDir(classificationPluginsDir);
        sucessfulUpdates++;
    }
    if (mDataManager->verifyPath(imageLoaderPluginsDir)) {
        mDataManager->saveImageLoaderPluginDir(imageLoaderPluginsDir);
        sucessfulUpdates++;
    }

    mSettingsView->pathsUpdated(sucessfulUpdates);
    mSettingsView->clearPaths();

}


