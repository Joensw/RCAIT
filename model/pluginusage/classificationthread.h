#ifndef CLASSIFICATIONTHREAD_H
#define CLASSIFICATIONTHREAD_H

#include "classificationpluginmanager.h"
#include <classificationresult.h>

class ClassificationThread : public QObject
{
    Q_OBJECT
public:
    ClassificationThread(QString pluginName, QString inputImageDirPath, QString trainDatasetPath, QString workingDirectory, QString modelName, ProgressablePlugin * receiver);
    ClassificationResult* getResult();

public slots:
    void slot_startClassification();

private:
        ProgressablePlugin* m_receiver;
        QString m_trainDatasetPath;
        QString m_inputImageDirPath;
        QString m_workingDirectory;
        QString m_pluginName;
        QString m_modelName;
        ClassificationResult* m_classificationResult;
        ClassificationPluginManager& m_classificationPluginManager = ClassificationPluginManager::getInstance();
};




#endif // CLASSIFICATIONTHREAD_H
