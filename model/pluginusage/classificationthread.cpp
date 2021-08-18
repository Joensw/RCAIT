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

}

void ClassificationThread::slot_startClassification()
{
    m_classificationResult = m_classificationPluginManager.classify(m_pluginName, m_inputImageDirPath, m_trainDatasetPath, m_workingDirectory, m_modelName, m_receiver);
    qDebug() << "Classification started";
}

void ClassificationThread::slot_makeProgress(int progress)
{

}
