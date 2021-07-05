#ifndef ADDPROJECTTASK_H
#define ADDPROJECTTASK_H

#include "task.h"

class AddProjectTask : public Task
{
public:
    AddProjectTask();
    AddProjectTask(QMap<QString, QVariant>);
};

#endif // ADDPROJECTTASK_H
