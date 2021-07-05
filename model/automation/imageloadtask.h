#ifndef IMAGELOADTASK_H
#define IMAGELOADTASK_H

#include "task.h"



class ImageLoadTask : public Task
{
public:
    ImageLoadTask();
    ImageLoadTask(QMap<QString, QVariant>);
};

#endif // IMAGELOADTASK_H
