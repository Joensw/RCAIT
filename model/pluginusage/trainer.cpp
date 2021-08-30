#include "trainer.h"

Trainer::Trainer()
{

}

void Trainer::train(const QString &pluginName, const QString &modelName, const QString &trainDatasetPath, const QString &validationDatasetPath, const QString &workingDirectory)
{
        m_recentWorkingDir = workingDirectory;
        m_trainWorker = new TrainingsThread(pluginName, modelName, trainDatasetPath, validationDatasetPath, workingDirectory, this);
        m_trainWorker->moveToThread(&trainThread);
        connect(&trainThread, &QThread::finished, m_trainWorker, &QObject::deleteLater);
        connect(&trainThread, &QThread::finished, this, &Trainer::slot_handleTrainingsResult);
        connect(this, &Trainer::sig_startTraining, m_trainWorker, &TrainingsThread::slot_startTraining);
        connect(this, &Trainer::sig_pluginFinished, this, &Trainer::slot_handleTrainingsResult);
        emit sig_progress(0);
        trainThread.start();
}

TrainingResult *Trainer::getLastTrainingResult()
{
    return m_trainingResults;
}

bool Trainer::getAugmentationPreview(const QString &pluginName, const QString &inputPath)
{
    return false;
}

QString Trainer::getRecentWorkingDir()
{
    return m_recentWorkingDir;
}

void Trainer::slot_handleTrainingsResult(){
    m_trainingResults = m_trainWorker->getResult();
    emit sig_progress(100);
    trainThread.quit();
    trainThread.wait();
    emit sig_trainingResultUpdated();
}

