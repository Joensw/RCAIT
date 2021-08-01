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
#include "imagecontroller.h"
#include "tabcontroller.h"

#include <QObject>

/**
 * @brief The Controller class creates and holds all the specific controllers and the application main window
 */
class Controller : public QObject {
    Q_OBJECT
public:
    /**
     * @brief Controller a Controller with the given parameters. Initialises all the other controllers and the data manager
     * @param parent optional parent object
     */
    explicit Controller(QObject *parent = nullptr);

public slots:
    /**
     * @brief slot_configurationComplete shows the main window of the application
     */
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

    ImageController* mImageController;

    TabController* mTabController;

    DataManager *mDataManger;


};

#endif // CONTROLLER_H
