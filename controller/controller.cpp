#include "controller.h"

Controller::Controller(QObject *parent) : QObject(parent)
{
    mDataManger = new DataManager;
    mSettingsController = new SettingsController(this, mDataManger);
    mMainWindow = new MainWindow;
    connect(mMainWindow, &MainWindow::sig_openSettings, mSettingsController, &SettingsController::slot_openSettings);
    mMainWindow->show();
}
