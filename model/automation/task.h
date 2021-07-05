#ifndef TASK_H
#define TASK_H

#include <pluginusage/progressable.h>

#include <DataManager.h>

enum TaskState
{
    IDLE,
    SCHEDULED,
    FAILED,
    COMPLETED,
    PERFORMING
};

class Task : public Progressable
{
public:
    Task(QString path, ModelManager *modelManager);
    void run();

signals:
    void sig_stateChanged(TaskState newState);

private:
    TaskState mState = IDLE;
    QString path;
    DataManager *mDataManager;
};

#endif // TASK_H
