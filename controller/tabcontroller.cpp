#include "tabcontroller.h"

enum tabs {
    _BEGIN = -1,
    START,
    IMPORT_FILES,
    IMAGE_INSPECTION,
    AI_TRAINING,
    INPUT_IMAGES,
    RESULTS,
    AUTOMATION,
    _END
};

TabController::TabController(CustomTabWidget *tWidget) {
    m_tabWidget = tWidget;
    //disable all tabs, except start and automation
    for (int i = _BEGIN + 1; i < _END; i++) {
        //#################
        //uncomment to enable:

        //m_tabWidget->setTabEnabled(i, false);

        //#################
    }
    m_tabWidget->setCurrentIndex(START);
}

void TabController::slot_openProject() {
    //disableTemporaryTabs();

    m_tabWidget->setTabEnabled(IMPORT_FILES, true);
    m_tabWidget->setCurrentIndex(IMPORT_FILES);
}

void TabController::slot_imagesLoaded() {
    m_tabWidget->setTabEnabled(IMAGE_INSPECTION, true);
}

void TabController::slot_modelLoaded() {
    m_tabWidget->setTabEnabled(INPUT_IMAGES, true);
    m_tabWidget->setTabEnabled(AI_TRAINING, true);
}

void TabController::disableTemporaryTabs() {
    for (int i = _BEGIN + 1; i < _END; i++) {
        m_tabWidget->setTabEnabled(i, false);
    }
}

