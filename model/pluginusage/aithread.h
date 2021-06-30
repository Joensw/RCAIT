#ifndef AITHREAD_H
#define AITHREAD_H

#include "model/pluginusage/progressable.h"

#include <QThread>

class AIThread : public QThread
{
public:
    AIThread();
    AIThread(Progressable* reciever, QString imagePath, QString modelName, QString pluginName, volatile bool* stopped);
private:
    Progressable* receiver;
    QString imagePath;
    QString modelName;
    volatile bool* stopped;
};

#endif // AITHREAD_H
