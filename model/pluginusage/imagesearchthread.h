#ifndef RCAIT_IMAGESEARCHTHREAD_H
#define RCAIT_IMAGESEARCHTHREAD_H

#include <QThread>
#include <pluginusage/progressableplugin.h>

class ImageSearchThread : public QThread {
    Q_OBJECT
    void run() override;

public:
    ImageSearchThread(ProgressablePlugin* receiver, QString imagePath, QString pluginName, int count, QStringList labels);

private:
    ProgressablePlugin* receiver;
    volatile bool* stopped;

};


#endif //RCAIT_IMAGESEARCHTHREAD_H
