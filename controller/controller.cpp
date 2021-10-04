/**
 * @file controller.cpp
 *
 * @brief holds and connects all the other controllers
 *
 * @author various
 */
#include "controller.h"

Controller::Controller(QObject *parent)
        : QObject(parent),
          mConfigurationController(new ConfigurationController(this)) {

    connect(&*mConfigurationController, &ConfigurationController::sig_configurationComplete, this,
            &Controller::slot_configurationComplete);
    mConfigurationController->verify();

}

void Controller::slot_configurationComplete(){
    mConfigurationController.reset();

    mDataManager = &DataManager::getInstance();

    mMainWindow.reset(new MainWindow);

    //Set member variables
    mSettingsController.reset(new SettingsController(this, mDataManager));
    mProjectController.reset(new ProjectController(this, mDataManager, mMainWindow->getStartWidget()));
    mModelController.reset(new ModelController(this, mDataManager, mMainWindow->getImportFilesWidget()));
    mAiController.reset(new AIController(mDataManager, mMainWindow->getInputImagesWidget(),
                                         mMainWindow->getAITrainingWidget()));
    mAutomationController.reset(new AutomationController(mMainWindow->getAutomationWidget()));
    mResultsController.reset(new ResultsController(mDataManager, mMainWindow->getResultsWidget()));
    mImageController.reset(
            new ImageController(mMainWindow->getImageInspectionWidget(), mMainWindow->getImportFilesWidget(),
                                mDataManager));
    mTabController.reset(new TabController(mMainWindow->getTabWidget(), mMainWindow->getResultsWidget()->getTabWidget()));

    //Connect Signals/Slots

    connect(&*mSettingsController, &SettingsController::sig_projectDirectoryChanged, &*mProjectController,
            &ProjectController::slot_projectDirectoryChanged);
    connect(mMainWindow->getStartWidget(), &StartWidget::sig_maximizeWindow, &*mMainWindow,
            &MainWindow::slot_maximizeWindow);
    connect(mMainWindow->getStartWidget(), &StartWidget::sig_normalizeWindow, &*mMainWindow,
            &MainWindow::slot_normalizeWindow);

    connect(&*mModelController, &ModelController::sig_modelLoaded, &*mTabController, &TabController::slot_modelLoaded);

    connect(&*mModelController, &ModelController::sig_modelLoaded, &*mAiController, &AIController::slot_modelLoaded);

    connect(&*mSettingsController, &SettingsController::sig_imagePluginsDirectoryChanged, &*mImageController,
            &ImageController::slot_imagePluginDirectoryChanged);
    connect(&*mProjectController, &ProjectController::sig_projectPathUpdated, &*mResultsController,
            &ResultsController::slot_projectPathUpdated);
    connect(&*mSettingsController, &SettingsController::sig_settingsApplied, &*mTabController,
            &TabController::slot_settingsSaved);




    connect(&*mProjectController, &ProjectController::sig_projectPathUpdated, &*mModelController,
            &ModelController::slot_projectPathUpdated);

    connect(&*mProjectController, &ProjectController::sig_projectPathUpdated, &*mTabController,
            &TabController::slot_openProject);
    connect(&*mProjectController, &ProjectController::sig_projectPathUpdated, &*mImageController,
            &ImageController::slot_openProject);

    connect(&*mMainWindow, &MainWindow::sig_openSettings, &*mSettingsController,
            &SettingsController::slot_openSettings);
    connect(&*mMainWindow, &MainWindow::sig_changedWindowState, mMainWindow->getStartWidget(),
            &StartWidget::slot_changedWindowState);

    connect(&*mImageController, &ImageController::sig_imagesUpdated, mMainWindow->getStartWidget(),
            &StartWidget::slot_imagesUpdated);
    connect(&*mImageController, &ImageController::sig_imagesUpdated, mMainWindow->getImageInspectionWidget(),
            &ImageInspectionWidget::slot_imagesUpdated);
    connect(&*mImageController, &ImageController::sig_startLoading, mMainWindow->getStartWidget(),
            &StartWidget::slot_startLoading);
    connect(&*mImageController, &ImageController::sig_startLoading, mMainWindow->getImageInspectionWidget(),
            &ImageInspectionWidget::slot_startLoading);

    connect(&*mAiController, &AIController::sig_trainingResultUpdated, &*mResultsController,
            &ResultsController::slot_addTrainingResult);
    connect(&*mAiController, &AIController::sig_classificationResultUpdated, &*mResultsController,
            &ResultsController::slot_addClassificationResult);

    connect(&*mAutomationController, &AutomationController::sig_trainingResultUpdated, &*mResultsController,
            &ResultsController::slot_addTrainingResult);

    connect(&*mAutomationController, &AutomationController::sig_classificationResultUpdated, &*mResultsController,
            &ResultsController::slot_addClassificationResult);
    connect(&*mAutomationController, &AutomationController::sig_projectDirectoryChanged, &*mResultsController,
            &ResultsController::slot_projectPathUpdated);
    connect(&*mAutomationController, &AutomationController::sig_projectDirectoryChanged, &*mProjectController,
            &ProjectController::slot_projectDirectoryChanged);

    connect(mMainWindow->getResultsWidget()->getTrainingResultsWidget(), &TrainingResultsWidget::sig_normal_loadTrainingResultData,
            &*mTabController, &TabController::slot_showTrainingResults);
    connect(mMainWindow->getResultsWidget()->getClassificationResultsWidget(), &ClassificationResultsWidget::sig_normal_loadClassificationResultData,
            &*mTabController, &TabController::slot_showTrainingResults);

    mMainWindow->show();
}

