#include "model/pluginusage/trainingsthread.h"



TrainingsThread::TrainingsThread(QString pluginName, QString modelName, QString trainDatasetPath, QString validationDatasetPath, QString workingDirectory, ProgressablePlugin * receiver)
{
    m_receiver = receiver;
    m_trainDatasetPath = trainDatasetPath;
    m_validationDatasetPath = validationDatasetPath;
    m_workingDirectory = workingDirectory;
    m_pluginName = pluginName;
    m_modelName = modelName;
}



void TrainingsThread::slot_startTraining()
{
    m_trainingResult = m_classificationPluginManager.train(m_pluginName,m_modelName,m_trainDatasetPath,m_validationDatasetPath, m_workingDirectory, m_receiver);
    qDebug() << "Training started: Comment in the actual call to the plugin in TrainingsThread and move sig->pluginfinished emission to plugin, if the program does not block on the return value";
    emit m_receiver->sig_pluginFinished();
}

TrainingResult *TrainingsThread::getResult() {
    return m_trainingResult;
}
