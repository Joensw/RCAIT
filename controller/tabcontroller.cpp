#include "tabcontroller.h"

enum tabs {
    $BEGIN = -1,
    START,
    IMPORT_FILES,
    IMAGE_INSPECTION,
    AI_TRAINING,
    INPUT_IMAGES,
    RESULTS,
    AUTOMATION,
    $END
};

TabController::TabController(CustomTabWidget *tabWidget)
        : m_tabWidget(tabWidget) {

    //disable all tabs, except start and automation
    for (int i = IMPORT_FILES; i < AUTOMATION; i++) {

        m_tabWidget->setTabEnabled(i, false);

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

void TabController::slot_showResults()
{
    m_tabWidget->setEnabled(RESULTS);
}

void TabController::disableDependentTabs() {
    for (int i = AI_TRAINING; i < RESULTS; i++) {
        m_tabWidget->setTabEnabled(i, false);
    }
}

