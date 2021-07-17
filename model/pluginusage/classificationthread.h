#ifndef CLASSIFICATIONTHREAD_H
#define CLASSIFICATIONTHREAD_H

#include "aithread.h"

#include <classificationresult.h>

class ClassificationThread : public AIThread
{
public:
    ClassificationThread(Progressable* receiver, QString imagePath, QString modelName, QString pluginName);
    ClassificationResult* getResult();

public slots:
    void slot_makeProgress(int progress);
};

#endif // CLASSIFICATIONTHREAD_H
