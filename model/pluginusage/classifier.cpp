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
    classifyThread.start();
    m_classificationWorker = new ClassificationThread(pluginName, inputImageDirPath, trainDatasetPath, workingDirectory, modelName, this);

}

void Classifier::slot_handleClassificationResult(){

}

ClassificationResult *Classifier::getLastClassificationResult()
{
    return nullptr;
}
