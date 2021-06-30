#ifndef CLASSIFIERTRAINER_H
#define CLASSIFIERTRAINER_H

#include "model/pluginusage/progressableplugin.h"
#include "plugins/classificationresult.h"
#include "plugins/trainingresult.h"

class ClassifierTrainer : public ProgressablePlugin
{
public:
    ClassifierTrainer();
    void train(QString pluginName, QString modelName, QString imagePath);
    void classify(QString pluginName, QString modelName, QString imagePath);
    TrainingResult* getLastTrainingResult();
    ClassificationResult* getLastClassificationResult();
    bool getAugmentationPreview(QString pluginName, QString inputPath);


signals:
    void sig_trainingResultUpdated();
    void sig_classificationResultUpdated();


private:
    TrainingResult* trainingResults;
    ClassificationResult* classificationResults;
};

#endif // CLASSIFIERTRAINER_H
