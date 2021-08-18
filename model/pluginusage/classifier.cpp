#include "classifier.h"

Classifier::Classifier()
{

}

void Classifier::classify(QString pluginName, QString inputImageDirPath, QString trainDatasetPath, QString workingDirectory, QString modelName)
{

    m_classificationWorker = new ClassificationThread(pluginName, inputImageDirPath, trainDatasetPath, workingDirectory, modelName, this);
    m_classificationWorker->moveToThread(&classifyThread);
    connect(&classifyThread, &QThread::finished, m_classificationWorker, &QObject::deleteLater);
    connect(&classifyThread, &QThread::finished, this, &Classifier::slot_handleClassificationResult);
    connect(this, &Classifier::sig_startClassification, m_classificationWorker, &ClassificationThread::slot_startClassification);
    connect(this, &Classifier::sig_pluginFinished, this, &Classifier::slot_handleClassificationResult);
    emit sig_progress(0);
    classifyThread.start();

}

void Classifier::slot_handleClassificationResult(){
    m_classificationResults = m_classificationWorker->getResult();
    emit sig_progress(100);
    classifyThread.quit();
    classifyThread.wait();

}

ClassificationResult *Classifier::getLastClassificationResult()
{
    return m_classificationResults;
}
