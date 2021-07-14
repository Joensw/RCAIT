#include "automationcontroller.h"

AutomationController::AutomationController(DataManager *dataManager, AutomationWidget * automationWidget)
{
    mDataManager = dataManager;
    mWidget = automationWidget;
    mAutomator = new Automator(mDataManager);
    connect(mWidget, &AutomationWidget::sig_start, this, &AutomationController::slot_start);
    connect(mWidget, &AutomationWidget::sig_stop, this, &AutomationController::slot_stop);
    connect(mWidget, &AutomationWidget::sig_import, this, &AutomationController::slot_import);
    connect(mWidget, &AutomationWidget::sig_remove, this, &AutomationController::slot_remove);
    connect(mWidget, &AutomationWidget::sig_queueAll, this, &AutomationController::slot_queueAll);
    connect(mWidget, &AutomationWidget::sig_queueSelected, this, &AutomationController::slot_queueSelected);
    connect(mWidget, &AutomationWidget::sig_unqueueAll, this, &AutomationController::slot_unqueueAll);
    connect(mWidget, &AutomationWidget::sig_unqueueSelected, this, &AutomationController::slot_unqueueSelected);

    connect(mAutomator, &Automator::sig_taskUpdate, mWidget, &AutomationWidget::slot_taskUpdate);


}

void AutomationController::slot_start()
{
    mAutomator->performTasks();
}

void AutomationController::slot_stop()
{
    mAutomator->stopTasks();
}

void AutomationController::slot_remove(int index)
{
    mAutomator->remove(index);
}

void AutomationController::slot_import(QString path)
{
    mAutomator->addTasks(path);
}

void AutomationController::slot_queueAll()
{
    int size = mAutomator->getUnqueuedSize();
    for (int i = size - 1; i >= 0; i--){
        mAutomator->queue(i);
    }
}

void AutomationController::slot_queueSelected(int index)
{
    mAutomator->queue(index);
}

void AutomationController::slot_unqueueAll()
{
    int size = mAutomator->getQueuedSize();
    for (int i = size - 1; i >= 0; i--){
        mAutomator->unqueue(i);
    }
}

void AutomationController::slot_unqueueSelected(int index)
{
    mAutomator->unqueue(index);
}