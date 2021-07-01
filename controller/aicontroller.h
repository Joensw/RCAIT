#ifndef AICONTROLLER_H
#define AICONTROLLER_H

#include <QString>
#include <inputimageswidget.h>

#include <model/pluginusage/classifiertrainer.h>



class AIController
{
public:
    //TODO: change DataManger and AITrainingTab to their respective types
    AIController(QString *dataManager, InputImagesWidget *inputImagesWidget, QString *AITrainingTab, ClassifierTrainer* classifierTrainer);

public slots:
    void slot_startTraining();
    void slot_abortTraining();
    void slot_results();
    void slot_trainingResultUpdated();
    void slot_classificationResultUpdated();
    void slot_startClassify(QString path);
    void slot_abortClassify();
    void slot_showAugmentationPreview();

private:
    //TODO: change DataManger and AITrainingTab to their respective types
    QString *dataManager;
    InputImagesWidget *inputImagesWidget;
    QString *aiTrainingTab;
    ClassifierTrainer* classifierTrainer;

    QString trainingPath;


    void train();
    void classify();
};

#endif // AICONTROLLER_H
