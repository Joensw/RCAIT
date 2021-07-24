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
    QList<Task*>::iterator i ;

    for (i = mQueuedTasks.begin(); i != mQueuedTasks.end() && !stop; ++i){
        //TODO change Task so it is stoppable
        connect((*i), &Task::sig_progress, this, &Automator::slot_makeProgress);
        (*i)->run();
        disconnect((*i), &Task::sig_progress, this, &Automator::slot_makeProgress);
        tasksCompleted++;
    }
}

void Automator::stopTasks()
{
    stop = true;
}

void Automator::addTasks(QString path)
{
    QFile jsonFile(path);
    jsonFile.open(QIODevice::ReadOnly | QIODevice::Text);
    QString jsonData = jsonFile.readAll();
    jsonFile.close();


    QJsonDocument doc = QJsonDocument::fromJson(jsonData.toUtf8());
    QVariantMap jsonMap = doc.object().toVariantMap();

    if (jsonMap.isEmpty() || !jsonMap.contains("taskType") || !jsonMap.contains("taskName") || !jsonMap.contains("projectName")){
        //TODO error message
        return;
    }
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
    int localProgress = (tasksCompleted * 100 + progress) / (mQueuedTasks.size() * 100);
    emit sig_progress(localProgress);
}

void Automator::slot_taskUpdated(QString taskName, TaskState state)
{
   QString StateMap[] = { "Scheduled", "Performing", "Failed", "Completed" };
   emit sig_taskUpdate(taskName, StateMap[state]);
}

