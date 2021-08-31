#include "trainer.h"

#include <qfuturewatcher.h>

Trainer::Trainer() = default;

void Trainer::train(const QString &pluginName, const QString &modelName, const QString &trainDatasetPath, const QString &validationDatasetPath, const QString &workingDirectory)
{
        m_recentWorkingDir = workingDirectory;
        auto watcher = new QFutureWatcher<TrainingResult*>;
        connect(watcher, &QFutureWatcher<int>::finished, this, &Trainer::slot_handleTrainingsResult);
        m_trainingResult = QtConcurrent::run(&ClassificationPluginManager::train, &mManager, pluginName, modelName, trainDatasetPath, validationDatasetPath, workingDirectory, this);
        watcher->setFuture(m_trainingResult);
        emit sig_progress(0);
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
    emit sig_progress(100);
    if (m_trainingResult.result()->isValid()) {
        emit sig_trainingResultUpdated(m_trainingResult.result());
    } else {
        qWarning() << "Invalid Training Result returned";
    }
}

void Trainer::slot_makeProgress(int progress)
{
    emit sig_progress(progress);
}

