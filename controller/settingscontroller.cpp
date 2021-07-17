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

//todo verify projects again at end, paths cant be changed to the same thing one by one!
void SettingsController::slot_applyGlobalSettings(QString projectsDir, QString classificationPluginsDir, QString imageLoaderPluginsDir)
{
    char sucessfulUpdates = 0;

    //this if condition is a bit ugly, we check for identical paths but have to make sure we ignore them incase they are empty
    //as on an empty path no change is performed
    if ( ((projectsDir == classificationPluginsDir) && (!projectsDir.isEmpty() && !classificationPluginsDir.isEmpty()))
        || ((projectsDir == imageLoaderPluginsDir) && (!projectsDir.isEmpty() && !imageLoaderPluginsDir.isEmpty()))
        || ((classificationPluginsDir == imageLoaderPluginsDir) && (!classificationPluginsDir.isEmpty() && !imageLoaderPluginsDir.isEmpty())) ) {
        mSettingsView->setGlobalSettingsError("Some of the specified paths are identical, the settings have not been applied!");
        return;
    }

    if (mDataManager->verifyPath(projectsDir)) {
        mDataManager->saveProjectsDir(projectsDir);
        mSettingsView->setCurrentProjectDirectory(projectsDir);
        emit sig_projectDirectoryChanged();
        sucessfulUpdates++;
    }
    if (mDataManager->verifyPath(classificationPluginsDir)) {
        mDataManager->saveClassificationPluginDir(classificationPluginsDir);
        mSettingsView->setCurrentClassificationPluginDirectory(classificationPluginsDir);
        //todo signal analog to above
        sucessfulUpdates++;
    }
    if (mDataManager->verifyPath(imageLoaderPluginsDir)) {
        mDataManager->saveImageLoaderPluginDir(imageLoaderPluginsDir);
        mSettingsView->setCurrentImageLoaderPluginDirectory(imageLoaderPluginsDir);
        //todo signal analog to above
        sucessfulUpdates++;
    }

    mSettingsView->pathsUpdated(sucessfulUpdates);
    mSettingsView->clearPaths();

}


