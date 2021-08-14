#include "controller.h"

Controller::Controller(QObject *parent) : QObject(parent)
{
    mDataManger = new DataManager;

    mMainWindow = new MainWindow;

    mConfigurationController = new  ConfigurationController(this, mDataManger);



    mSettingsController = new SettingsController(this, mDataManger);
    mProjectController = new ProjectController(this, mDataManger, mMainWindow->getStartWidget());
    mModelController = new ModelController(this , mDataManger, mMainWindow->getImportFilesWidget());
    mAiController = new AIController(mDataManger, mMainWindow->getInputImagesWidget(), mMainWindow->getAITrainingWidget());
    mAutomationController = new AutomationController(mDataManger, mMainWindow->getAutomationWidget());
    mResultsController = new ResultsController(mDataManger, mMainWindow->getResultsWidget());
    mImageController = new ImageController(mMainWindow->getImageInspectionWidget(),mMainWindow->getImportFilesWidget(),mDataManger);
    mTabController = new TabController(mMainWindow->getTabWidget());

    connect(mMainWindow->getStartWidget(), &StartWidget::sig_openProject, mTabController, &TabController::slot_openProject);
    connect(mMainWindow->getStartWidget(), &StartWidget::sig_openProject, mImageController, &ImageController::slot_openProject);
    connect(mSettingsController, &SettingsController::sig_projectDirectoryChanged, mProjectController, &ProjectController::slot_projectDirectoryChanged);
    connect(mMainWindow->getStartWidget(), &StartWidget::sig_maximizeWindow, mMainWindow, &MainWindow::slot_maximizeWindow);
    connect(mMainWindow->getStartWidget(), &StartWidget::sig_normalizeWindow, mMainWindow, &MainWindow::slot_normalizeWindow);
    connect(mConfigurationController, &ConfigurationController::sig_configurationComplete, this, &Controller::slot_configurationComplete);
    connect(mImageController, &ImageController::sig_imagesLoaded, mTabController, &TabController::slot_imagesLoaded);
    connect(mModelController, &ModelController::sig_modelLoaded, mTabController, &TabController::slot_modelLoaded);

    connect(mSettingsController, &SettingsController::sig_imagePluginsDirectoryChanged, mImageController, &ImageController::slot_imagePluginDirectoryChanged);
    connect(mProjectController, &ProjectController::sig_projectPathUpdated, mResultsController, &ResultsController::slot_projectPathUpdated);

    mConfigurationController->verify();

    connect(mMainWindow, &MainWindow::sig_openSettings, mSettingsController, &SettingsController::slot_openSettings);
    connect(mMainWindow, &MainWindow::sig_changedWindowState, mMainWindow->getStartWidget(), &StartWidget::slot_changedWindowState);
}

void Controller::slot_configurationComplete()
{
    delete mConfigurationController;
    mProjectController->refresh();
    mDataManger->setUp();
    mMainWindow->show();
}

