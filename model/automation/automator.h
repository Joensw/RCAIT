#ifndef AUTOMATOR_H
#define AUTOMATOR_H

#include "task.h"

#include <datamanager.h>

#include <pluginusage/progressable.h>



class Automator : public Progressable
{
    Q_OBJECT
public:
    Automator(DataManager *dataManager);

    void performTasks();
    void addTasks(QString path);
    void remove(int taskNum);
    void unqueue(int taskNum);
    void queue(int taskNum);

    int getUnqueuedSize();
    int getQueuedSize();

    QList<QString> getUnqueuedTasks();
    QList<QString> getQueuedTasks();

public slots:
    void slot_taskUpdated(QString name, TaskState state);
    void stopTasks();

signals:
    void sig_taskUpdate(QString name, QString state);


private:
    QList<Task*> mUnqueuedTasks;
    QList<Task*> mQueuedTasks;
    DataManager *mDataManager;
    bool stop = false;
};

#endif // AUTOMATOR_H
