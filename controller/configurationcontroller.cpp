/**
 * @file configurationcontroller.cpp
 *
 * @brief insures program vital information is present before use of the applications
 *
 * @author Jonas Wille
 */
#include "configurationcontroller.h"


ConfigurationController::ConfigurationController(QObject *parent)
        : QObject(parent),
          mConfigurationDialog(new ConfigurationDialog),
          mSettingsManager(&SettingsManager::getInstance()){

    mConfigurationDialog->setAttribute(Qt::WA_DeleteOnClose, true);
    mConfigurationDialog->setModal(true);
    connect(&*mConfigurationDialog, &ConfigurationDialog::sig_directoriesSpecified, this,
            &ConfigurationController::slot_directoriesSpecified);
}

void
ConfigurationController::slot_directoriesSpecified(const QString &projectDir, const QString &classificationPluginDir,
                                                   const QString &imageLoaderPluginsDir, const QString &pythonPath) {
    if (SettingsManager::verifyPaths({projectDir, classificationPluginDir, imageLoaderPluginsDir, pythonPath})) {
        mSettingsManager->configureSettingsFile(projectDir, classificationPluginDir, imageLoaderPluginsDir, pythonPath);
        mConfigurationDialog->confirm();
        mSettingsManager->reload();
        emit sig_configurationComplete();
        return;
    }
    mConfigurationDialog->showError();
}

void ConfigurationController::verify() {
    if (!mSettingsManager->verifyDirectories()) {
        mConfigurationDialog->open();
        return;
    }
    emit sig_configurationComplete();
}


