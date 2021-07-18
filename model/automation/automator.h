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

    //probably never used
    QList<QString> getUnqueuedTasks();
    //probably never used
    QList<QString> getQueuedTasks();

public slots:
    void slot_makeProgress(int progress) override;

    void slot_taskUpdated(QString name, TaskState state);
    void stopTasks();

signals:
    void sig_taskUpdate(QString name, QString state);
    void sig_taskAdded(QString name);
    void sig_progress(int);


private:
    QList<Task*> mUnqueuedTasks;
    QList<Task*> mQueuedTasks;
    DataManager *mDataManager;
    bool stop = false;
    int tasksCompleted = 0;
};

#endif // AUTOMATOR_H
