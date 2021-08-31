#include "classifier.h"

#include <qfuturewatcher.h>

Classifier::Classifier() = default;

void Classifier::classify(const QString &pluginName, const QString &inputImageDirPath, const QString &trainDatasetPath,
                          const QString &workingDirectory, const QString &modelName) {

    auto watcher = new QFutureWatcher<ClassificationResult*>;
    connect(watcher, &QFutureWatcher<int>::finished, this, &Classifier::slot_handleClassificationResult);
    m_classificationResult = QtConcurrent::run(&ClassificationPluginManager::classify, &mManager, pluginName, inputImageDirPath, trainDatasetPath, workingDirectory, modelName, this);
    watcher->setFuture(m_classificationResult);
    emit sig_progress(0);

}

void Classifier::slot_handleClassificationResult() {
    emit sig_progress(100);
    if (m_classificationResult.result()->isValid()) {
        emit sig_classificationResultUpdated(m_classificationResult.result());
    } else {
        qWarning() << "Invalid Classification Result returned";
    }

}

void Classifier::slot_makeProgress(int progress) {
    emit sig_progress(progress);
}

bool Classifier::getAugmentationPreview(const QString &pluginName, const QString &inputPath) {
    //TODO Fill
    return false;
}
