#ifndef TRAININGSTHREAD_H
#define TRAININGSTHREAD_H

#include <results/trainingresult.h>
#include "model/pluginusage/aithread.h"
#include "classificationpluginmanager.h"

class TrainingsThread : public QObject
{
    Q_OBJECT
public:
    TrainingsThread(QString pluginName, QString modelName, QString trainDatasetPath, QString validationDatasetPath, QString workingDirectory, ProgressablePlugin * receiver);
    ~TrainingsThread() {};
    TrainingResult* getResult();

public slots:
    void slot_startTraining();

private:
        ProgressablePlugin* m_receiver;
        QString m_trainDatasetPath;
        QString m_validationDatasetPath;
        QString m_workingDirectory;
        QString m_pluginName;
        QString m_modelName;
        TrainingResult* m_trainingResult;
        ClassificationPluginManager& m_classificationPluginManager = ClassificationPluginManager::getInstance();
};

#endif // TRAININGSTHREAD_H
