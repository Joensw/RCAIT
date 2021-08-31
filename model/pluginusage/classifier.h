#ifndef CLASSIFIER_H
#define CLASSIFIER_H
#include <plugins/results/trainingresult.h>
#include <classificationpluginmanager.h>
#include "model/pluginusage/progressableplugin.h"
#include "plugins/results/classificationresult.h"

class Classifier : public ProgressablePlugin
{
    Q_OBJECT

public:
    Classifier();

    void classify(const QString& pluginName, const QString& inputImageDirPath, const QString& trainDatasetPath, const QString& workingDirectory, const QString& modelName);
    bool getAugmentationPreview(const QString& pluginName, const QString& inputPath);


signals:
    void sig_classificationResultUpdated(ClassificationResult* classificationResult);
    void sig_startClassification();

public slots:
    void slot_handleClassificationResult();
    void slot_makeProgress(int progress) override;

private:
    ClassificationPluginManager& mManager = ClassificationPluginManager::getInstance();
    QFuture<ClassificationResult *> m_classificationResult;

};

#endif // CLASSIFIER_H
