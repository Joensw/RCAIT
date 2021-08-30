#ifndef TRAINER_H
#define TRAINER_H

#include <plugins/results/trainingresult.h>
#include "model/pluginusage/progressableplugin.h"
#include "plugins/results/classificationresult.h"
#include "trainingsthread.h"
#include "classificationthread.h"

class Trainer : public ProgressablePlugin
{
    Q_OBJECT
    QThread trainThread;

public:
    Trainer();
    ~Trainer() {
            trainThread.quit();
            trainThread.wait();
    }

    void train(const QString &pluginName, const QString &modelName, const QString &trainDatasetPath, const QString &validationDatasetPath, const QString &workingDirectory);
    TrainingResult* getLastTrainingResult();
    bool getAugmentationPreview(const QString &pluginName, const QString &inputPath);

    QString getRecentWorkingDir();


signals:
    void sig_trainingResultUpdated();
    void sig_startTraining();

public slots:
    void slot_handleTrainingsResult();

private:
    TrainingResult* m_trainingResults;
    TrainingsThread *m_trainWorker;

    QString m_recentWorkingDir;


};

#endif // TRAINER_H
