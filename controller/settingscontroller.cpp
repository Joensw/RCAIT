/**
 * @file settingscontroller.cpp
 *
 * @brief connects the logic of the settings with the visual user interface
 *
 * @author Jonas Wille
 */
#include "settingscontroller.h"


SettingsController::SettingsController(QObject *parent, DataManager *dataManager)
        : QObject(parent),
          mDataManager(dataManager) {

    mSettingsView.reset(new SettingsView(nullptr, mDataManager->getPluginNames(), mDataManager->getPluginSettings()));
    connect(&*mSettingsView, &SettingsView::sig_applyGlobalSettings, this,
            &SettingsController::slot_applyGlobalSettings);
    connect(&*mSettingsView, &SettingsView::sig_applySettings, this, &SettingsController::slot_applySettings);
}

void SettingsController::slot_openSettings() {
    mSettingsView->show();
    mSettingsView->retranslateUi();
    mSettingsView->setCurrentProjectDirectory(mDataManager->getProjectsDir());
    mSettingsView->setCurrentClassificationPluginDirectory(mDataManager->getClassificationPluginDir());
    mSettingsView->setCurrentImageLoaderPluginDirectory(mDataManager->getImageLoaderPluginDir());
}

void SettingsController::slot_applySettings(int index) {
    mDataManager->savePluginSettings(index);
}

void SettingsController::slot_applyGlobalSettings(QString projectDir, QString classificationPluginDir,
                                                  QString imageLoaderPluginDir, QString pythonPath) {
    QString errorMessage;
    int successfulUpdates = 0;
    if (mDataManager->applyGlobalSettings(std::move(projectDir), std::move(classificationPluginDir),
                                          std::move(imageLoaderPluginDir), std::move(pythonPath), &errorMessage,
                                          &successfulUpdates)) {
        mSettingsView->setCurrentProjectDirectory(mDataManager->getProjectsDir());
        mSettingsView->setCurrentClassificationPluginDirectory(mDataManager->getClassificationPluginDir());
        mSettingsView->setCurrentImageLoaderPluginDirectory(mDataManager->getImageLoaderPluginDir());
        mSettingsView->setCurrentPythonExecutablePath(mDataManager->getImageLoaderPluginDir());
        mSettingsView->pathsUpdated(successfulUpdates);
        mSettingsView->clearPaths();
        emit sig_projectDirectoryChanged(mDataManager->getProjectsDir());
        emit sig_imagePluginsDirectoryChanged(mDataManager->getImageLoaderPluginDir());
        mSettingsView->addPluginWidgets(mDataManager->getPluginNames(), mDataManager->getPluginSettings());
        return;
    }
    mSettingsView->setGlobalSettingsError(errorMessage);
}


