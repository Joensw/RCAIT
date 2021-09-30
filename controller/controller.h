/**
 * @file controller.h
 *
 * @brief holds and connects all the other controllers
 *
 * @author various
 */
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
class Controller final : public QObject {
Q_OBJECT
public:
    /**
     * @brief Controller a Controller with the given parameters. Initialises all the other controllers and the data manager
     * @param parent optional parent object
     */
    explicit Controller(QObject *parent = nullptr);

    /**
     * @brief operator = deleted assignment operator
     */

    Controller &operator=(const Controller &) = delete;

public slots:

    /**
     * @brief slot_configurationComplete shows the main window of the application
     */
    void slot_configurationComplete();

private:
    DataManager *mDataManager;

    QScopedPointer<MainWindow> mMainWindow;

    QScopedPointer<ConfigurationController> mConfigurationController;

    QScopedPointer<SettingsController> mSettingsController;

    QScopedPointer<ProjectController> mProjectController;

    QScopedPointer<AIController> mAiController;

    QScopedPointer<ResultsController> mResultsController;

    QScopedPointer<ModelController> mModelController;

    QScopedPointer<AutomationController> mAutomationController;

    QScopedPointer<ImageController> mImageController;

    QScopedPointer<TabController> mTabController;

};

#endif // CONTROLLER_H
