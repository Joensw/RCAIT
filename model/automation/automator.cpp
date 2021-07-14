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
    while (!stop && !mQueuedTasks.empty()){
        //TODO change Task so it is stoppable
         mQueuedTasks.at(0)->run();
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

    if (jsonMap.isEmpty() || jsonMap.firstKey() != "taskType" || !jsonMap.contains("projectName")){
        //TODO error message
        return;
    }
    mUnqueuedTasks.append(new Task(jsonMap, mDataManager));
}

void Automator::remove(int taskNum)
{
    mUnqueuedTasks.remove(taskNum);
}

void Automator::unqueue(int taskNum)
{
    mUnqueuedTasks.append(mQueuedTasks.at(taskNum));
    mQueuedTasks.remove(taskNum);
}

void Automator::queue(int taskNum)
{
    mQueuedTasks.append(mUnqueuedTasks.at(taskNum));
    mUnqueuedTasks.remove(taskNum);
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
    //TODO implement
    return QStringList();
}

QList<QString> Automator::getQueuedTasks()
{
    //TODO implement
    return QStringList();
}

void Automator::slot_taskUpdated()
{
    //TODO implement
}

