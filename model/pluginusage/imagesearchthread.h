#ifndef IMAGESEARCHTHREAD_H
#define IMAGESEARCHTHREAD_H

#include "model/pluginusage/progressable.h"

#include <QThread>



class ImageSearchThread : public QThread
{
public:
    ImageSearchThread(Progressable* receiver, QString imagePath, QString pluginName, int count, QStringList labels);
private:
    Progressable* receiver;
    volatile bool* stopped;
};

#endif // IMAGESEARCHTHREAD_H
