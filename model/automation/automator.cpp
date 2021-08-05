#include "automator.h"

#include <QJsonDocument>
#include <QJsonObject>



Automator::Automator(DataManager *dataManager)
{
    mDataManager = dataManager;
}

void Automator::performTasks()
{
    stop = false;
 // QList<Task*>::iterator i;
    tasksCompleted = 0;

    for (mRunningTask = mQueuedTasks.begin(); mRunningTask != mQueuedTasks.end() && !stop; ++mRunningTask){
        if ((*mRunningTask)->getState() == COMPLETED || (*mRunningTask)->getState() == FAILED){
            tasksCompleted++;
            continue;
        }

        connect((*mRunningTask), &Task::sig_progress, this, &Automator::slot_makeProgress);
        connect((*mRunningTask), &Task::sig_stateChanged, this, &Automator::slot_taskUpdated);
        (*mRunningTask)->run();
        disconnect((*mRunningTask), &Task::sig_progress, this, &Automator::slot_makeProgress);
        disconnect((*mRunningTask), &Task::sig_stateChanged, this, &Automator::slot_taskUpdated);
        tasksCompleted++;
    }
    emit sig_progress(100);
}

void Automator::stopTasks()
{
    stop = true;
    (*mRunningTask)->abort();
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
        //TODO error message
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
    Task* task = new Task(jsonMap, mDataManager);
    if (!task->isValid()) return;
    mUnqueuedTasks.append(task);
    emit sig_taskAdded(jsonMap.value("taskName").toString());
    emit sig_taskUpdate(mUnqueuedTasks.last()->getName(), "Not_Scheduled");
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

QList<QString> Automator::getUnqueuedTasks()
{
    QStringList list;
    for (Task* task : mUnqueuedTasks){
        list.append(task->getName());
    }
    return list;
}

QList<QString> Automator::getQueuedTasks()
{
    QStringList list;
    for (Task* task : mQueuedTasks){
        list.append(task->getName());
    }
    return list;
}

void Automator::slot_makeProgress(int progress)
{
    int localProgress = (tasksCompleted * 100 + progress) / (mQueuedTasks.size());
    emit sig_progress(localProgress);
}

void Automator::slot_taskUpdated(QString taskName, TaskState state)
{
   QString StateMap[] = { "Scheduled", "Performing", "Failed", "Completed" };
   emit sig_taskUpdate(taskName, StateMap[state]);
}

