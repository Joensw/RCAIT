#include "classificationthread.h"


ClassificationThread::ClassificationThread(QString pluginName, QString inputImageDirPath, QString trainDatasetPath, QString workingDirectory, QString modelName, ProgressablePlugin * receiver)
{
    m_receiver = receiver;
    m_trainDatasetPath = trainDatasetPath;
    m_inputImageDirPath = inputImageDirPath;
    m_workingDirectory = workingDirectory;
    m_pluginName = pluginName;
    m_modelName = modelName;
}

ClassificationResult *ClassificationThread::getResult()
{
    return m_classificationResult;
}

void ClassificationThread::slot_startClassification()
{
    m_classificationResult = m_classificationPluginManager.classify(m_pluginName, m_inputImageDirPath, m_trainDatasetPath, m_workingDirectory, m_modelName, m_receiver);
    qDebug() << "Classification started: Comment in the actual call to the plugin in ClassifiactionThread and move sig pluginfinished to plugin";
    emit m_receiver->sig_pluginFinished();
}


