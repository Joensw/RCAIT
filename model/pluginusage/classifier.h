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
    ~Classifier() override {
            classifyThread.quit();
            classifyThread.wait();
    }

    void classify(const QString& pluginName, const QString& inputImageDirPath, const QString& trainDatasetPath, const QString& workingDirectory, const QString& modelName);
    bool getAugmentationPreview(const QString& pluginName, const QString& inputPath);


signals:
    void sig_classificationResultUpdated(ClassificationResult* classificationResult);
    void sig_startClassification();

public slots:
    void slot_handleClassificationResult();
    void slot_makeProgress(int progress) override;

private:
    ClassificationResult* m_classificationResults;
    ClassificationThread *m_classificationWorker;

};

#endif // CLASSIFIER_H
