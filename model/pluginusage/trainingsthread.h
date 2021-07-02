#ifndef TRAININGSTHREAD_H
#define TRAININGSTHREAD_H

#include <results/TrainingResult.h>
#include "model/pluginusage/aithread.h"

class TrainingsThread : public AIThread
{
public:
    TrainingsThread(Progressable* receiver, QString imagePath, QString modelName, QString pluginName);
    TrainingResult* getResult();

public slots:
    void slot_makeProgress(int progress);
};

#endif // TRAININGSTHREAD_H
