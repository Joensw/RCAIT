#ifndef CLASSIFIER_H
#define CLASSIFIER_H
#include <plugins/results/trainingresult.h>
#include "model/pluginusage/progressableplugin.h"
#include "plugins/results/classificationresult.h"
#include "trainingsthread.h"
#include "classificationthread.h"

class Classifier : public ProgressablePlugin
{
    Q_OBJECT
    QThread classifyThread;

public:
    Classifier();
    ~Classifier() {
            classifyThread.quit();
            classifyThread.wait();
    }

    void classify(QString pluginName, QString inputImageDirPath, QString trainDatasetPath, QString workingDirectory, QString modelName);
    ClassificationResult* getLastClassificationResult();
    bool getAugmentationPreview(QString pluginName, QString inputPath);


signals:
    void sig_classificationResultUpdated(ClassificationResult* classificationResult);
    void sig_startClassification();

public slots:
    void slot_handleClassificationResult();

private:
    ClassificationResult* m_classificationResults;
    ClassificationThread *m_classificationWorker;

};

#endif // CLASSIFIER_H
