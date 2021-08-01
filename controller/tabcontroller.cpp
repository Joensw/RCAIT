#include "tabcontroller.h"

int startTabIndex = 0;
int importFilesTabIndex = 1;
int imageInspectionTabIndex = 2;
int AITrainingTabIndex = 3;
int inputImagesTabIndex = 4;
int resultsTabIndex = 5;
int automationTabIndex = 6;

TabController::TabController(CustomTabWidget *tWidget)
{
    m_tabWidget = tWidget;
    //disable all tabs, except start and automation
    for (int i = importFilesTabIndex; i < automationTabIndex; i++){
        //#################
        //uncomment to enable:

        //m_tabWidget->setTabEnabled(i, false);

        //#################
    }
    m_tabWidget->setCurrentIndex(startTabIndex);
}

void TabController::slot_openProject()
{
    //disableTemporaryTabs();

    m_tabWidget->setTabEnabled(importFilesTabIndex, true);
    int newIndex = m_tabWidget->currentIndex() + 1;
    m_tabWidget->setCurrentIndex(newIndex);
}

void TabController::slot_imagesLoaded()
{
    m_tabWidget->setTabEnabled(imageInspectionTabIndex, true);
}

void TabController::slot_modelLoaded()
{
    m_tabWidget->setTabEnabled(inputImagesTabIndex, true);
    m_tabWidget->setTabEnabled(AITrainingTabIndex, true);
}

void TabController::disableTemporaryTabs()
{
    for (int i = importFilesTabIndex; i < automationTabIndex; i++){
        m_tabWidget->setTabEnabled(i, false);
    }
}

