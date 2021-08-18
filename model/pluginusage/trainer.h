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

    void train(QString pluginName, QString modelName, QString trainDatasetPath, QString validationDatasetPath, QString workingDirectory);
    TrainingResult* getLastTrainingResult();
    bool getAugmentationPreview(QString pluginName, QString inputPath);


signals:
    void sig_trainingResultUpdated();
    void sig_startTraining();

public slots:
    void slot_handleTrainingsResult();

private:
    TrainingResult* m_trainingResults;
    TrainingsThread *m_trainWorker;


};

#endif // TRAINER_H
