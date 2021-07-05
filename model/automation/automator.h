#ifndef AUTOMATOR_H
#define AUTOMATOR_H

#include "task.h"

#include <DataManager.h>

#include <pluginusage/progressable.h>



class Automator : public Progressable
{
public:
    Automator(DataManager *dataManager);

    void performTasks();
    void addTasks(QString path);
    void remove(int taskNum);
    void setIdle(int taskNum);
    void schedule(int taskNum);
    QList<QString> getIdleTasks();
    QList<QString> getSheduledTasks();

public slots:
    void slot_taskUpdated();

signals:
    void sig_taskUpdate();


private:
    QList<Task*> mIdleTask;
    QList<Task*> mSheduledTask;
    DataManager *mDataManager;
};

#endif // AUTOMATOR_H
