#include "controller.h"

Controller::Controller(QObject *parent) : QObject(parent) {

    mConfigurationController.reset(new ConfigurationController(this));

    connect(&*mConfigurationController, &ConfigurationController::sig_configurationComplete, this,
            &Controller::slot_configurationComplete);
    mConfigurationController->verify();

}

void Controller::slot_configurationComplete() {
    mConfigurationController.reset();

    mMainWindow.reset(new MainWindow);
    mDataManager.reset(new DataManager);

    mSettingsController.reset(new SettingsController(this, &*mDataManager));
    mProjectController.reset(new ProjectController(this, &*mDataManager, mMainWindow->getStartWidget()));
    mModelController.reset(new ModelController(this, &*mDataManager, mMainWindow->getImportFilesWidget()));
    mAiController.reset(new AIController(&*mDataManager, mMainWindow->getInputImagesWidget(),
                                         mMainWindow->getAITrainingWidget()));
    mAutomationController.reset(new AutomationController(&*mDataManager, mMainWindow->getAutomationWidget()));
    mResultsController.reset(new ResultsController(&*mDataManager, mMainWindow->getResultsWidget()));
    mImageController.reset(new ImageController(mMainWindow->getImageInspectionWidget(), mMainWindow->getImportFilesWidget(),
                                           &*mDataManager));
    mTabController.reset(new TabController(mMainWindow->getTabWidget()));

    connect(mMainWindow->getStartWidget(), &StartWidget::sig_openProject, &*mTabController,
            &TabController::slot_openProject);
    connect(mMainWindow->getStartWidget(), &StartWidget::sig_openProject, &*mImageController,
            &ImageController::slot_openProject);
    connect(&*mSettingsController, &SettingsController::sig_projectDirectoryChanged, &*mProjectController,
            &ProjectController::slot_projectDirectoryChanged);
    connect(mMainWindow->getStartWidget(), &StartWidget::sig_maximizeWindow, &*mMainWindow,
            &MainWindow::slot_maximizeWindow);
    connect(mMainWindow->getStartWidget(), &StartWidget::sig_normalizeWindow, &*mMainWindow,
            &MainWindow::slot_normalizeWindow);

    connect(&*mImageController, &ImageController::sig_imagesLoaded, &*mTabController, &TabController::slot_imagesLoaded);
    connect(&*mModelController, &ModelController::sig_modelLoaded, &*mTabController, &TabController::slot_modelLoaded);

    connect(&*mSettingsController, &SettingsController::sig_imagePluginsDirectoryChanged, &*mImageController,
            &ImageController::slot_imagePluginDirectoryChanged);
    connect(&*mProjectController, &ProjectController::sig_projectPathUpdated, &*mResultsController,
            &ResultsController::slot_projectPathUpdated);

    connect(&*mProjectController, &ProjectController::sig_projectPathUpdated, &*mModelController,
            &ModelController::slot_projectPathUpdated);

    connect(&*mMainWindow, &MainWindow::sig_openSettings, &*mSettingsController, &SettingsController::slot_openSettings);
    connect(&*mMainWindow, &MainWindow::sig_changedWindowState, mMainWindow->getStartWidget(),
            &StartWidget::slot_changedWindowState);

    mMainWindow->show();
}

