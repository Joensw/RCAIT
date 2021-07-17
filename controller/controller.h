#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "settingscontroller.h"
#include "projectcontroller.h"
#include "datamanager.h"
#include "aicontroller.h"
#include "modelcontroller.h"
#include "automationcontroller.h"
#include "configurationcontroller.h"
#include "resultscontroller.h"
#include <mainwindow.h>

#include <QObject>


class Controller : public QObject {
Q_OBJECT
public:
    explicit Controller(QObject *parent = nullptr);

public slots:
    void slot_configurationComplete();

private:
    MainWindow *mMainWindow;

    SettingsController *mSettingsController;

    ProjectController *mProjectController;

    AIController *mAiController;

    ResultsController *mResultsController;

    ModelController *mModelController;

    AutomationController *mAutomationController;

    ConfigurationController * mConfigurationController;

    DataManager *mDataManger;


};

#endif // CONTROLLER_H
