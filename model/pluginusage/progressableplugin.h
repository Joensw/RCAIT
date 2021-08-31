#ifndef PROGRESSABLEPLUGIN_H
#define PROGRESSABLEPLUGIN_H

#include "model/pluginusage/progressable.h"

class ProgressablePlugin : public Progressable
{
    Q_OBJECT
public:
    ProgressablePlugin() = default;

public slots:
    void slot_makeProgress(int progress) override = 0;

signals:
    void sig_pluginStarted();
    void sig_pluginAborted();
    void sig_pluginFinished();
    void sig_progress(int progress);
    void sig_statusUpdate(QString status);


private:
    volatile bool stopped;
    bool classificationFinished;


};

#endif // PROGRESSABLEPLUGIN_H
