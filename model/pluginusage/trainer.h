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

    [[maybe_unused]] bool getAugmentationPreview(const QString &pluginName, const QString &inputPath);

    QString getRecentWorkingDir();


signals:
    void sig_trainingResultUpdated(TrainingResult *trainingResult);
    void sig_startTraining();

public slots:
    void slot_handleTrainingsResult();
    void slot_makeProgress(int progress) override;

private:
    ClassificationPluginManager& mManager = ClassificationPluginManager::getInstance();
    QString m_recentWorkingDir;
    QFuture<TrainingResult *> m_trainingResult;



};

#endif // TRAINER_H
