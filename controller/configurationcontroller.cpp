#include "configurationcontroller.h"



ConfigurationController::ConfigurationController(QObject *parent, DataManager *dataManager) : QObject(parent)
{
    this->mDataManager = dataManager;
    mConfigurationDialog = new ConfigurationDialog();
    mConfigurationDialog->setAttribute(Qt::WA_DeleteOnClose, true);
    mConfigurationDialog->setModal(true);
    connect(mConfigurationDialog, &ConfigurationDialog::sig_directoriesSpecified, this, &ConfigurationController::slot_directoriesSpecified);
}

void ConfigurationController::slot_directoriesSpecified(QString projectsDir, QString classificationPluginsDir, QString imageLoaderPluginsDir)
{
    if(mDataManager->verifyPaths(projectsDir, classificationPluginsDir, imageLoaderPluginsDir)){
        mDataManager->saveProjectsDir(projectsDir);
        mDataManager->saveClassificationPluginDir(classificationPluginsDir);
        mDataManager->saveImageLoaderPluginDir(imageLoaderPluginsDir);
        mConfigurationDialog->confirm();
        emit sig_configurationComplete();
        return;
    }
    mConfigurationDialog->showError();
}

void  ConfigurationController::verify(){
    if (!mDataManager->verifyDirectories()) {
        mConfigurationDialog->open();
        return;
    }
    emit sig_configurationComplete();
}


