#include "classifier.h"

Classifier::Classifier() = default;

void Classifier::classify(const QString &pluginName, const QString &inputImageDirPath, const QString &trainDatasetPath,
                          const QString &workingDirectory, const QString &modelName) {

    m_classificationWorker = new ClassificationThread(pluginName, inputImageDirPath, trainDatasetPath, workingDirectory,
                                                      modelName, this);
    m_classificationWorker->moveToThread(&classifyThread);
    connect(&classifyThread, &QThread::finished, m_classificationWorker, &QObject::deleteLater);
    connect(&classifyThread, &QThread::finished, this, &Classifier::slot_handleClassificationResult);
    connect(this, &Classifier::sig_startClassification, m_classificationWorker,
            &ClassificationThread::slot_startClassification);
    connect(this, &Classifier::sig_pluginFinished, this, &Classifier::slot_handleClassificationResult);
    emit sig_progress(0);
    classifyThread.start();

}

void Classifier::slot_handleClassificationResult() {
    //ClassificationResult *classificationResult = m_classificationWorker->getResult();
    m_classificationResults = m_classificationWorker->getResult();
    emit sig_progress(100);
    classifyThread.quit();
    classifyThread.wait();
    if (m_classificationResults->isValid()) {
        emit sig_classificationResultUpdated(m_classificationResults);
    } else {
        qWarning() << "Invalid Classification Result returned";
    }

}
