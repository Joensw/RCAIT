#include "controller.h"

Controller::Controller(QObject *parent) : QObject(parent)
{
    mDataManger = new DataManager;

    mMainWindow = new MainWindow;

    mConfigurationController = new  ConfigurationController(this, mDataManger);
    connect(mConfigurationController, &ConfigurationController::sig_configurationComplete, this, &Controller::slot_configurationComplete);

    mSettingsController = new SettingsController(this, mDataManger);
    mProjectController = new ProjectController(this, mDataManger, mMainWindow->getStartWidget());
    mModelController = new ModelController(this , mDataManger, mMainWindow->getImportFilesWidget());
    mAiController = new AIController(mDataManger, mMainWindow->getInputImagesWidget(), mMainWindow->getAITrainingWidget());
    mAutomationController = new AutomationController(mDataManger, mMainWindow->getAutomationWidget());
    mResultsController = new ResultsController(mDataManger, mMainWindow->getResultsWidget());
    mImageController = new ImageController(mMainWindow->getImageSectionWidget(),mMainWindow->getImportFilesWidget(),mDataManger);
    connect(mMainWindow->getStartWidget(), &StartWidget::sig_openProject, mImageController, &ImageController::slot_openProject);
    connect(mSettingsController, &SettingsController::sig_projectDirectoryChanged, mProjectController, &ProjectController::slot_projectDirectoryChanged);
    connect(mSettingsController, &SettingsController::sig_imagePluginsDirectoryChanged, mImageController, &ImageController::slot_imagePluginDirectoryChanged);

    mConfigurationController->verify();


    connect(mMainWindow, &MainWindow::sig_openSettings, mSettingsController, &SettingsController::slot_openSettings);
}

void Controller::slot_configurationComplete()
{
    delete mConfigurationController; //isnt needed anymore
    mProjectController->refresh();
    mMainWindow->show();

}

