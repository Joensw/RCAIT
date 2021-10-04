/**
 * @file tabcontroller.h
 *
 * @brief manage the available tabs of the applications
 *
 * @author Jonas Wille
 */
#include "tabcontroller.h"

/**
 * @brief The tabs enum assigns variables representing the tabs of the mainwindow their respective number
 */

enum mainTabs {
    $BEGIN_MAIN = -1,
    START,
    IMPORT_FILES,
    IMAGE_INSPECTION,
    AI_TRAINING,
    INPUT_IMAGES,
    RESULTS,
    AUTOMATION,
    $END_MAIN
};

enum resultsUnderTabs {
    $BEGIN_RESULTS = -1,
    TRAINING,
    CLASSIFICATION,
    $END_RESULTS
};

TabController::TabController(CustomTabWidget *tabWidget, QTabWidget* resultsTabWidget)
        : m_tabWidget(tabWidget), m_resultsTabWidget(resultsTabWidget) {

    //disable all tabs, except start and automation
    for (int i = IMPORT_FILES; i < AUTOMATION; i++) {

        m_tabWidget->setTabEnabled(i, false);

    }
    for (int j = TRAINING; j <= CLASSIFICATION; j++) {
        m_resultsTabWidget->setTabEnabled(j, false);
    }
    m_tabWidget->setCurrentIndex(START);
}

void TabController::slot_openProject() {
    disableDependentTabs();
    m_tabWidget->setTabEnabled(IMPORT_FILES, true);
    m_tabWidget->setCurrentIndex(IMPORT_FILES);
    m_tabWidget->setTabEnabled(IMAGE_INSPECTION, true);
}

void TabController::slot_modelLoaded() {
    m_tabWidget->setTabEnabled(INPUT_IMAGES, true);
    m_tabWidget->setTabEnabled(AI_TRAINING, true);
}

void TabController::slot_showTrainingResults()
{
     m_tabWidget->setTabEnabled(RESULTS, true);
     m_resultsTabWidget->setTabEnabled(TRAINING, true);
     m_resultsTabWidget->setCurrentIndex(TRAINING);
}

void TabController::slot_showClassificationResults()
{
     m_tabWidget->setTabEnabled(RESULTS, true);
     m_resultsTabWidget->setTabEnabled(CLASSIFICATION, true);
     m_resultsTabWidget->setCurrentIndex(CLASSIFICATION);
}

void TabController::slot_settingsSaved()
{
    m_tabWidget->setTabEnabled(AI_TRAINING, false);
}

void TabController::disableDependentTabs() {
    for (int i = AI_TRAINING; i < RESULTS; i++) {
        m_tabWidget->setTabEnabled(i, false);
    }
}

