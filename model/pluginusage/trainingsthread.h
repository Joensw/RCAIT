#ifndef TRAININGSTHREAD_H
#define TRAININGSTHREAD_H

#include "model/pluginusage/aithread.h"
#include "plugins/trainingresult.h"

class TrainingsThread : public AIThread
{
public:
    TrainingsThread(Progressable* reciever, QString imagePath, QString modelName, QString pluginName);
    TrainingResult* getResult();

public slots:
    void slot_makeProgress(int progress);
};

#endif // TRAININGSTHREAD_H
