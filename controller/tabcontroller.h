/**
 * @file tabcontroller.h
 *
 * @brief manage the available tabs of the applications
 *
 * @author Jonas Wille
 */
#ifndef TABCONTROLLER_H
#define TABCONTROLLER_H

#include "customtabwidget.h"

/**
 * @brief The TabController class controls which widgets are selectable at certain times during the programs execution
 */
class TabController : public QObject
{
     Q_OBJECT
public:
    /**
     * @brief TabController creates a new tabController
     * @param tabWidget a CustomTabWidget argument
     */
    TabController(CustomTabWidget *tabWidget);
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
     * @brief slot_showResults called when the results tab is to be shown in the ui
     */
    void slot_showResults();
private:
    void disableDependentTabs();

    CustomTabWidget * m_tabWidget;
};

#endif // TABCONTROLLER_H
