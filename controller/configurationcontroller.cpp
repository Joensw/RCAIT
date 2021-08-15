#include "configurationcontroller.h"



ConfigurationController::ConfigurationController(QObject *parent) : QObject(parent)
{
    mConfigurationDialog = new ConfigurationDialog();
    mConfigurationDialog->setAttribute(Qt::WA_DeleteOnClose, true);
    mConfigurationDialog->setModal(true);
    connect(mConfigurationDialog, &ConfigurationDialog::sig_directoriesSpecified, this, &ConfigurationController::slot_directoriesSpecified);
    mSettingsManager = new SettingsManager(true);
}

void ConfigurationController::slot_directoriesSpecified(QString projectDir, QString classificationPluginDir, QString imageLoaderPluginsDir)
{
    if(mSettingsManager->verifyPaths(projectDir, classificationPluginDir, imageLoaderPluginsDir)){
        mSettingsManager->configureSettingsFile(projectDir, classificationPluginDir, imageLoaderPluginsDir);
        mConfigurationDialog->confirm();
        emit sig_configurationComplete();
        return;
    }
    mConfigurationDialog->showError();
}

void  ConfigurationController::verify(){
    if (!mSettingsManager->verifyDirectories()) {
        mConfigurationDialog->open();
        return;
    }
    emit sig_configurationComplete();
}


