#ifndef TRAININGTASK_H
#define TRAININGTASK_H

#include "task.h"

#include <pluginusage/trainingsthread.h>

class TrainingTask : public Task
{
public:
    TrainingTask();
    TrainingTask(QMap<QString, QVariant>);

private:
    TrainingsThread *mTrainer;
};

#endif // TRAININGTASK_H
