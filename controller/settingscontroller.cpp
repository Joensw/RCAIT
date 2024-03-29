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

    mSettingsView.reset(new SettingsView(nullptr, mDataManager->getPluginNames(), mDataManager->getPluginSettings(), mDataManager->getPluginIcons()));
    connect(&*mSettingsView, &SettingsView::sig_applyGlobalSettings, this,
            &SettingsController::slot_applyGlobalSettings);
    connect(&*mSettingsView, &SettingsView::sig_applySettings, this, &SettingsController::slot_applySettings);
    mSettingsView->setAttribute(Qt::WA_QuitOnClose, false);
}

void SettingsController::slot_openSettings() {
    mSettingsView->show();
    mSettingsView->retranslateUi();
    mSettingsView->setCurrentProjectDirectory(mDataManager->getProjectsDir());
    mSettingsView->setCurrentClassificationPluginDirectory(mDataManager->getClassificationPluginDir());
    mSettingsView->setCurrentImageLoaderPluginDirectory(mDataManager->getImageLoaderPluginDir());
    mSettingsView->setCurrentPythonExecutablePath(mDataManager->getPythonExecutablePath());
}

void SettingsController::slot_applySettings(int index) {
    mDataManager->savePluginSettings(index);
}

void SettingsController::slot_applyGlobalSettings(QString projectDir, QString classificationPluginDir,
                                                  QString imageLoaderPluginDir, QString pythonPath) {
    QString errorMessage;
    int successfulUpdates;
    if (mDataManager->applyGlobalSettings(std::move(projectDir), std::move(classificationPluginDir),
                                          std::move(imageLoaderPluginDir), std::move(pythonPath), errorMessage,
                                          successfulUpdates)) {
        mSettingsView->setCurrentProjectDirectory(mDataManager->getProjectsDir());
        mSettingsView->setCurrentClassificationPluginDirectory(mDataManager->getClassificationPluginDir());
        mSettingsView->setCurrentImageLoaderPluginDirectory(mDataManager->getImageLoaderPluginDir());
        mSettingsView->setCurrentPythonExecutablePath(mDataManager->getPythonExecutablePath());
        mSettingsView->pathsUpdated(successfulUpdates);
        mSettingsView->clearPaths();
        emit sig_projectDirectoryChanged(mDataManager->getProjectsDir());
        emit sig_imagePluginsDirectoryChanged(mDataManager->getImageLoaderPluginDir());
        emit sig_settingsApplied();
        mSettingsView->addPluginWidgets(mDataManager->getPluginNames(), mDataManager->getPluginSettings(), mDataManager->getPluginIcons());
        return;
    }
    mSettingsView->setGlobalSettingsError(errorMessage);
}


