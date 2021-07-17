#include "controller.h"

Controller::Controller(QObject *parent) : QObject(parent)
{
    mDataManger = new DataManager;
    mMainWindow = new MainWindow;
    mSettingsController = new SettingsController(this, mDataManger);
    mProjectController = new ProjectController(this, mDataManger, mMainWindow->getStartWidget());
    mModelController = new ModelController(this , mDataManger, mMainWindow->getImportFilesWidget());
    mAiController = new AIController(mDataManger, mMainWindow->getInputImagesWidget(), mMainWindow->getAITrainingWidget());
    mAutomationController = new AutomationController(mDataManger, mMainWindow->getAutomationWidget());
    mResultsController = new ResultsController(mDataManger, mMainWindow->getResultsWidget());

    connect(mMainWindow, &MainWindow::sig_openSettings, mSettingsController, &SettingsController::slot_openSettings);

    mMainWindow->show();
}
