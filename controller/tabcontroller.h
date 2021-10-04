/**
 * @file tabcontroller.h
 *
 * @brief manage the available tabs of the applications
 *
 * @author Jonas Wille
 */
#ifndef TABCONTROLLER_H
#define TABCONTROLLER_H

#include <customtabwidget.h>
#include <resultswidget.h>
#include <QTabWidget>

/**
 * @brief The TabController class controls which widgets are selectable at certain times during the programs execution
 */
class TabController final : public QObject
{
     Q_OBJECT
public:
    /**
     * @brief TabController creates a new tabController
     * @param tabWidget a CustomTabWidget argument
     * @param resultsWidget ResultsWidget argument
     */
    TabController(CustomTabWidget* tabWidget, QTabWidget* resultsTabWidget);

    /**
     * @brief operator = deleted assignment operator
     * @return
     */
    TabController &operator=(const TabController &) = delete;
public slots:
    /**
     * @brief slot_openProject called when a project is openened, unlocks the importFilesTab
     */
    void slot_openProject();
    /**
     * @brief slot_modelLoaded called when a model is loaded, unlocks the inputImages- and AITrainingTab
     */
    void slot_modelLoaded();

    /**
     * @brief slot_showResults called when the training tab is to be enabled in the ui
     */
    void slot_showTrainingResults();

    /**
     * @brief slot_showResults called when the classification tab is to be enabled in the ui
     */
    void slot_showClassificationResults();

    /**
     * @brief slot_settingsSaved called when the global settings are saved, as plugins might have changed.
     */
    void slot_settingsSaved();
private:
    void disableDependentTabs();

    CustomTabWidget *m_tabWidget;

    QTabWidget *m_resultsTabWidget;

};

#endif // TABCONTROLLER_H
