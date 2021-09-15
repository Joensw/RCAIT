#include "automator.h"

#include <QJsonDocument>



Automator::Automator() = default;

void Automator::performTasks()
{
    stop = false;
    tasksCompleted = 0;

    for (mRunningTask = mQueuedTasks.begin(); mRunningTask != mQueuedTasks.end() && !stop; ++mRunningTask){
        if ((*mRunningTask)->getState() == COMPLETED || (*mRunningTask)->getState() == FAILED){
            tasksCompleted++;
            continue;
        }

        connect((*mRunningTask), &Task::sig_progress, this, &Automator::slot_makeProgress);
        connect((*mRunningTask), &Task::sig_stateChanged, this, &Automator::slot_taskUpdated);
        connect((*mRunningTask), &Task::sig_classificationResultUpdated, this, &Automator::sig_classificationResultUpdated);
        connect((*mRunningTask), &Task::sig_trainingResultUpdated, this, &Automator::sig_trainingResultUpdated);
        (*mRunningTask)->run();
        disconnect((*mRunningTask), &Task::sig_progress, this, &Automator::slot_makeProgress);
        disconnect((*mRunningTask), &Task::sig_stateChanged, this, &Automator::slot_taskUpdated);
        tasksCompleted++;
    }
    emit sig_progress(100);
    emit sig_finished();
}

void Automator::stopTasks()
{
    stop = true;
    if (mRunningTask != mQueuedTasks.end()){
        (*mRunningTask)->abort();
    }
}

void Automator::addTasks(QString path)
{
    //Open json
    QFile jsonFile(path);
    jsonFile.open(QIODevice::ReadOnly | QIODevice::Text);
    QString jsonData = jsonFile.readAll();
    jsonFile.close();

    //convert to variantmap
    QJsonDocument doc = QJsonDocument::fromJson(jsonData.toUtf8());
    QVariantMap jsonMap = doc.object().toVariantMap();

    //check for required task keys
    if (jsonMap.isEmpty() || !jsonMap.contains("taskType") || !jsonMap.contains("taskName") || !jsonMap.contains("projectName")){
        return;
    }

    //check if task with same name already exists
    QString name = jsonMap.value("taskName").toString();
    for (int i = 0; i < mQueuedTasks.size(); i++){
        if(mQueuedTasks.at(i)->getName() == name) return;
    }
    for (int i = 0; i < mUnqueuedTasks.size(); i++){
        if(mUnqueuedTasks.at(i)->getName() == name) return;
    }

    //create task and add to list
    Task* task = new Task(jsonMap);
    if (!task->isValid()) return;
    mUnqueuedTasks.append(task);
    emit sig_taskAdded(jsonMap.value("taskName").toString());
    emit sig_taskUpdate(mUnqueuedTasks.last()->getName(), "Not_Scheduled");
    emit sig_projectCreated();
}

void Automator::remove(int taskNum)
{
    mUnqueuedTasks.remove(taskNum);
}

void Automator::unqueue(int taskNum)
{
    mUnqueuedTasks.append(mQueuedTasks.at(taskNum));
    mQueuedTasks.remove(taskNum);
    emit sig_taskUpdate(mUnqueuedTasks.last()->getName(), "Not_Scheduled");
}

void Automator::queue(int taskNum)
{
    mQueuedTasks.append(mUnqueuedTasks.at(taskNum));
    mUnqueuedTasks.remove(taskNum);
    mQueuedTasks.last()->resetTask();
    emit sig_taskUpdate(mQueuedTasks.last()->getName(), "Scheduled");
}

int Automator::getUnqueuedSize()
{
    return mUnqueuedTasks.size();
}

int Automator::getQueuedSize()
{
    return mQueuedTasks.size();
}

void Automator::slot_makeProgress(int progress)
{
    int localProgress = (tasksCompleted * 100 + progress) / (mQueuedTasks.size());
    emit sig_progress(localProgress);
}

void Automator::slot_taskUpdated(const QString &taskName, TaskState state)
{
   QString StateMap[] = { "Scheduled", "Performing", "Failed", "Completed" };
   emit sig_taskUpdate(taskName, StateMap[state]);
}

