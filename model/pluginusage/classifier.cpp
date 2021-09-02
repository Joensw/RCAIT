#include "classifier.h"

#include <qfuturewatcher.h>

Classifier::Classifier() = default;

void Classifier::classify(const QString &pluginName, const QString &inputImageDirPath, const QString &trainDatasetPath,
                          const QString &workingDirectory, const QString &modelName) {

    auto watcher = new QFutureWatcher<ClassificationResult*>;
    connect(watcher, &QFutureWatcher<ClassificationResult*>::finished, this, &Classifier::slot_handleClassificationResult);
    mClassificationResult = QtConcurrent::run(&ClassificationPluginManager::classify, &mManager, pluginName, inputImageDirPath, trainDatasetPath, workingDirectory, modelName, this);
    watcher->setFuture(mClassificationResult);
    emit sig_progress(0);

}



void Classifier::slot_handleClassificationResult() {
    emit sig_progress(100);
    if (mClassificationResult.result()->isValid()) {
        emit sig_classificationResultUpdated(mClassificationResult.result());
    } else {
        qWarning() << "Invalid Classification Result returned";
    }

}

void Classifier::slot_makeProgress(int progress) {
    emit sig_progress(progress);
}

