/**
 * @file automationcontroller.cpp
 *
 * @brief connects the automation interface with the automation logic
 *
 * @author Adrian Nelson
 */
#include "automationcontroller.h"

AutomationController::AutomationController(AutomationWidget *automationWidget)
        : mWidget(automationWidget),
          mAutomator(new Automator()) {

    connect(mWidget, &AutomationWidget::sig_start, this, &AutomationController::slot_start);
    connect(mWidget, &AutomationWidget::sig_stop, this, &AutomationController::slot_stop);
    connect(mWidget, &AutomationWidget::sig_import, this, &AutomationController::slot_import);
    connect(mWidget, &AutomationWidget::sig_remove, this, &AutomationController::slot_remove);
    connect(mWidget, &AutomationWidget::sig_queueAll, this, &AutomationController::slot_queueAll);
    connect(mWidget, &AutomationWidget::sig_queueSelected, this, &AutomationController::slot_queueSelected);
    connect(mWidget, &AutomationWidget::sig_unqueueAll, this, &AutomationController::slot_unqueueAll);
    connect(mWidget, &AutomationWidget::sig_unqueueSelected, this, &AutomationController::slot_unqueueSelected);

    connect(&*mAutomator, &Automator::sig_trainingResultUpdated, this, &AutomationController::sig_trainingResultUpdated);
    connect(&*mAutomator, &Automator::sig_classificationResultUpdated, this, &AutomationController::sig_classificationResultUpdated);
    connect(&*mAutomator, &Automator::sig_projectCreated, this, &AutomationController::sig_projectDirectoryChanged);

    connect(&*mAutomator, &Automator::sig_taskAdded, mWidget, &AutomationWidget::slot_taskAdded);
    connect(&*mAutomator, &Automator::sig_taskUpdate, mWidget, &AutomationWidget::slot_taskUpdate);
    connect(&*mAutomator, &Automator::sig_progress, mWidget, &AutomationWidget::slot_progress);
    connect(&*mAutomator, &Automator::sig_finished, mWidget, &AutomationWidget::slot_finished);




}

void AutomationController::slot_start() {
    auto task = QtConcurrent::run(&Automator::performTasks, &*mAutomator);
    Q_UNUSED(task)
}

void AutomationController::slot_stop() {
    mAutomator->stopTasks();
}

void AutomationController::slot_remove(int index) {
    mAutomator->remove(index);
}

void AutomationController::slot_import(QString path) {
    mAutomator->addTasks(std::move(path));
}

void AutomationController::slot_queueAll() {
    int size = mAutomator->getUnqueuedSize();
    for (int i = 0; i < size; ++i) {
        mAutomator->queue(0);
    }
}

void AutomationController::slot_queueSelected(int index) {
    mAutomator->queue(index);
}

void AutomationController::slot_unqueueAll() {
    int size = mAutomator->getQueuedSize();
    for (int i = 0; i < size; ++i) {
        mAutomator->unqueue(0);
    }
}

void AutomationController::slot_unqueueSelected(int index) {
    mAutomator->unqueue(index);
}
