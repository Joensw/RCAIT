#ifndef AITHREAD_H
#define AITHREAD_H

#include "model/pluginusage/progressable.h"

#include <QThread>

class AIThread : public QThread {
public:
    AIThread() = default;

    //TODO What is this used for?
    AIThread(Progressable *receiver, QString imagePath, QString modelName, QString pluginName, volatile bool *stopped);

private:
    //TODO Are these needed?
    Progressable *receiver;
    QString imagePath;
    QString modelName;
    volatile bool *stopped;
};

#endif // AITHREAD_H
