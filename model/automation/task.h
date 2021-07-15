#ifndef TASK_H
#define TASK_H

#include "command.h"

#include <pluginusage/progressable.h>

#include <datamanager.h>

enum TaskState
{
    SCHEDULED,
    PERFORMING,
    FAILED,
    COMPLETED
};
QString StateMap[] = { "Scheduled", "Performing", "Failed", "Completed" };

class Task : public Progressable
{
    Q_OBJECT
public:
    Task(QVariantMap map, DataManager *dataManager);

    QString getName();
    void run();

public slots:
    void slot_saveTrainingResult(TrainingResult result);
    void slot_saveClassificationResult(ClassificationResult result);


signals:
    void sig_stateChanged(TaskState newState);



private:
    QString mName;
    TaskState mState = SCHEDULED;
    QString mProjectPath;
    DataManager *mDataManager;
    QList<Command*> mCommandList;
};

#endif // TASK_H
