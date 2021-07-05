#ifndef CLASSIFICATIONTASK_H
#define CLASSIFICATIONTASK_H

#include "task.h"

class ClassificationTask : public Task
{
public:
    ClassificationTask();
    ClassificationTask(QMap<QString, QVariant>);

private:
   // ClassificationThread *mTrainer;
};

#endif // CLASSIFICATIONTASK_H
