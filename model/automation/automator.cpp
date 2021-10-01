#include "automator.h"


Automator::Automator() = default;

void Automator::performTasks() {
    stop = false;
    tasksCompleted = 0;

    for (mRunningTask = mQueuedTasks.begin(); mRunningTask != mQueuedTasks.end() && !stop; ++mRunningTask) {
        auto runningTask = *mRunningTask;
        if (runningTask->getState() == COMPLETED || runningTask->getState() == FAILED) {
            tasksCompleted++;
            continue;
        }

        connect(&*runningTask, &Task::sig_progress, this, &Automator::slot_makeProgress);
        connect(&*runningTask, &Task::sig_stateChanged, this, &Automator::slot_taskUpdated);
        connect(&*runningTask, &Task::sig_classificationResultUpdated, this,
                &Automator::sig_classificationResultUpdated);
        connect(&*runningTask, &Task::sig_trainingResultUpdated, this, &Automator::sig_trainingResultUpdated);

        runningTask->run();

        disconnect(&*runningTask, &Task::sig_progress, this, &Automator::slot_makeProgress);
        disconnect(&*runningTask, &Task::sig_stateChanged, this, &Automator::slot_taskUpdated);
        tasksCompleted++;
    }
    emit sig_progress(100);
    emit sig_finished();
}

void Automator::stopTasks() {
    stop = true;
    if (mRunningTask != mQueuedTasks.end()) {
        (*mRunningTask)->abort();
    }
}

void Automator::addTasks(const QString &path) {
    QJsonObject jsonObject = JSON_Toolbox::readJSONFromFile(path);
    QVariantMap jsonMap = jsonObject.toVariantMap();

    //check for required task keys
    if (jsonMap.isEmpty() || !jsonMap.contains("taskType") || !jsonMap.contains("taskName") ||
        !jsonMap.contains("projectName")) {
        return;
    }

    //check if task with same name already exists
    QString name = jsonMap["taskName"].toString();
    for (const auto &mQueuedTask: mQueuedTasks) {
        if (mQueuedTask->getName() == name) return;
    }
    for (const auto &mUnqueuedTask: mUnqueuedTasks) {
        if (mUnqueuedTask->getName() == name) return;
    }

    //create task and add to list
    auto task = QSharedPointer<Task>(new Task(jsonMap), &QObject::deleteLater);
    if (!task->isValid()) return;
    mUnqueuedTasks << task;
    emit sig_taskAdded(jsonMap["taskName"].toString());
    emit sig_taskUpdate(mUnqueuedTasks.last()->getName(), StateMap[NOT_SCHEDULED]);
    emit sig_projectCreated();
}

void Automator::remove(int taskNum) {
    mUnqueuedTasks.remove(taskNum);
}

void Automator::unqueue(int taskNum) {
    mUnqueuedTasks << mQueuedTasks[taskNum];
    mQueuedTasks.remove(taskNum);
    emit sig_taskUpdate(mUnqueuedTasks.last()->getName(), StateMap[NOT_SCHEDULED]);
}

void Automator::queue(int taskNum) {
    mQueuedTasks << mUnqueuedTasks[taskNum];
    mUnqueuedTasks.remove(taskNum);
    mQueuedTasks.last()->resetTask();
    emit sig_taskUpdate(mQueuedTasks.last()->getName(), StateMap[SCHEDULED]);
}

qsizetype Automator::getUnqueuedSize() const {
    return mUnqueuedTasks.size();
}

qsizetype Automator::getQueuedSize() const {
    return mQueuedTasks.size();
}

void Automator::slot_makeProgress(int progress) {
    auto localProgress = (tasksCompleted * 100 + progress) / (mQueuedTasks.size());
    emit sig_progress((int) localProgress);
}

void Automator::slot_taskUpdated(const QString &taskName, TaskState state) {
    emit sig_taskUpdate(taskName, StateMap[state]);
}

