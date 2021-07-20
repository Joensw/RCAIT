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
    char sucessfulUpdates = 0;

    QString tempProjectsDir = mDataManager->getProjectsDir();
    QString tempClassificationPluginDir = mDataManager->getClassificationPluginDir();
    QString tempImageLoaderPluginDir = mDataManager->getImageLoaderPluginDir();

    if (!projectsDir.isEmpty()) {
        sucessfulUpdates++;
        tempProjectsDir = projectsDir;
    }
    if (!classificationPluginsDir.isEmpty()) {
        //todo signal analog to above
        sucessfulUpdates++;
        tempClassificationPluginDir = classificationPluginsDir;
    }
    if (!imageLoaderPluginsDir.isEmpty()) {
        //todo signal analog to above
        sucessfulUpdates++;
        tempImageLoaderPluginDir = imageLoaderPluginsDir;
    }
    //above: basically check if there is actual update, ie. isnt empty,
    //below: check if all paths are allowed / valid, and if any of them are overlapping
    if (mDataManager->verifyPaths(tempProjectsDir, tempClassificationPluginDir, tempImageLoaderPluginDir)){
        mDataManager->saveProjectsDir(tempProjectsDir);
        mDataManager->saveClassificationPluginDir(tempClassificationPluginDir);
        mDataManager->saveImageLoaderPluginDir(tempImageLoaderPluginDir);

        mSettingsView->setCurrentProjectDirectory(tempProjectsDir);
        mSettingsView->setCurrentClassificationPluginDirectory(tempClassificationPluginDir);
        mSettingsView->setCurrentImageLoaderPluginDirectory(tempImageLoaderPluginDir);

        mSettingsView->pathsUpdated(sucessfulUpdates);
        mSettingsView->clearPaths();

        emit sig_projectDirectoryChanged();
        return;

    }
    //new structure isnt allowed
    mSettingsView->setGlobalSettingsError(tr("Settings have not been updated, there is a conflict.\n"
                                             "paths may not be identical and must exist, this includes new and unchanged paths"));


}


