#ifndef AICONTROLLER_H
#define AICONTROLLER_H

#include <QString>
#include <aitrainingwidget.h>
#include <datamanager.h>
#include <inputimageswidget.h>

#include <model/pluginusage/classifiertrainer.h>



class AIController : public QObject

{
    Q_OBJECT
public:
    AIController(DataManager *dataManager, InputImagesWidget *inputImagesWidget, AITrainingWidget *AITrainingWidget);

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
    DataManager *mDataManager;
    InputImagesWidget *mInputImagesWidget;
    AITrainingWidget *mAiTrainingWidget;
    ClassifierTrainer* mClassifierTrainer;

    QString mTrainingPath;


    void train();
    void classify();
};

#endif // AICONTROLLER_H
