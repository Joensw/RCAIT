#ifndef TASK_H
#define TASK_H

#include "command.h"

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
    Q_OBJECT
public:
    Task(QVariantMap path, DataManager *dataManager);
    void run();

public slots:
    void slot_saveTrainingResult(TrainingResult result);
    void slot_saveClassificationResult(ClassificationResult result);


signals:
    void sig_stateChanged(TaskState newState);



private:
    TaskState mState = IDLE;
    QString mProjectPath;
    DataManager *mDataManager;
    QList<Command*> mCommandList;
};

#endif // TASK_H
