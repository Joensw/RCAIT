#include "trainer.h"

Trainer::Trainer()
{

}

void Trainer::train(QString pluginName, QString modelName, QString trainDatasetPath, QString validationDatasetPath, QString workingDirectory)
{
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

bool Trainer::getAugmentationPreview(QString pluginName, QString inputPath)
{
    return false;
}

void Trainer::slot_handleTrainingsResult(){
    m_trainingResults = m_trainWorker->getResult();
    emit sig_progress(100);
    trainThread.quit();
    trainThread.wait();
}

