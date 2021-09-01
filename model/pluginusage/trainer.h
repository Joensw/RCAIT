#ifndef TRAINER_H
#define TRAINER_H

#include <trainingresult.h>
#include <qfuture.h>
#include <classificationpluginmanager.h>
#include "progressableplugin.h"
#include "classificationresult.h"

class Trainer : public ProgressablePlugin
{
    Q_OBJECT

public:
    Trainer();

    void train(const QString &pluginName, const QString &modelName, const QString &trainDatasetPath, const QString &validationDatasetPath, const QString &workingDirectory);

    void getAugmentationPreview(const QString& pluginName, const QString& modelName, const QString& inputPath, const QString& targetPath, int amount);

    QString getRecentWorkingDir();


signals:
    void sig_trainingResultUpdated(TrainingResult *trainingResult);
    void sig_startTraining();
    void sig_augmentationPreviewReady(bool success, QString targetpath);

public slots:
    void slot_handleTrainingsResult();
    void slot_handleAugmentationResult();
    void slot_makeProgress(int progress) override;

private:
    ClassificationPluginManager& mManager = ClassificationPluginManager::getInstance();
    QString mRecentWorkingDir;
    QString mRecentTargetPath;
    QFuture<TrainingResult *> m_trainingResult;
    QFuture<bool> mAugmentationSuccess;



};

#endif // TRAINER_H
