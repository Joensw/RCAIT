#include "trainer.h"

#include <qfuturewatcher.h>

Trainer::Trainer() = default;

void Trainer::train(const QString &pluginName, const QString &modelName, const QString &trainDatasetPath, const QString &validationDatasetPath, const QString &workingDirectory)
{
        mRecentWorkingDir = workingDirectory;
        auto watcher = new QFutureWatcher<TrainingResult*>;
        connect(watcher, &QFutureWatcher<TrainingResult*>::finished, this, &Trainer::slot_handleTrainingsResult);
        connect(watcher, &QFutureWatcher<TrainingResult*>::finished, watcher, &QFutureWatcher<TrainingResult*>::deleteLater);
        m_trainingResult = QtConcurrent::run(&ClassificationPluginManager::train, &mManager, pluginName, modelName, trainDatasetPath, validationDatasetPath, workingDirectory, this);
        watcher->setFuture(m_trainingResult);
        emit sig_progress(0);
}

void Trainer::getAugmentationPreview(const QString &pluginName, const QString &modelName, const QString &inputPath, const QString &targetPath, int amount)
{
    mRecentTargetPath = targetPath;
    auto watcher = new QFutureWatcher<bool>;
    connect(watcher, &QFutureWatcher<bool>::finished, this, &Trainer::slot_handleAugmentationResult);
    connect(watcher, &QFutureWatcher<bool>::finished, watcher, &QFutureWatcher<bool>::deleteLater);
    mAugmentationSuccess = QtConcurrent::run(&ClassificationPluginManager::getAugmentationPreview, &mManager, pluginName, modelName, inputPath, targetPath, amount);
    watcher->setFuture(mAugmentationSuccess);
}

QString Trainer::getRecentWorkingDir()
{
    return mRecentWorkingDir;
}

void Trainer::slot_handleTrainingsResult(){
    emit sig_progress(100);
    if (m_trainingResult.result()->isValid()) {
        emit sig_trainingResultUpdated(m_trainingResult.result());
    } else {
        qWarning() << "Invalid Training Result returned";
    }
}

void Trainer::slot_handleAugmentationResult()
{
    emit sig_augmentationPreviewReady(mAugmentationSuccess.result(), mRecentTargetPath);
}

void Trainer::slot_makeProgress(int progress)
{
    emit sig_progress(progress);
}

