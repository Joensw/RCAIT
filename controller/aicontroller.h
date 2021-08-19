#ifndef AICONTROLLER_H
#define AICONTROLLER_H

#include <QString>
#include <aitrainingwidget.h>
#include <datamanager.h>
#include <inputimageswidget.h>
#include "classifier.h"
#include "trainer.h"



/**
 * @brief The AIController class mediates between ui elements and classification/training.
 */
class AIController : public QObject

{
    Q_OBJECT
public:
    /**
     * @brief AIController constructs an AIController.
     *
     * @param dataManager Source of general information.
     * @param inputImagesWidget Source for additional information needed for classification.
     * @param AITrainingWidget Source for additional information needed for training.
     */
    AIController(DataManager *dataManager, InputImagesWidget *inputImagesWidget, AITrainingWidget *AITrainingWidget);

public slots:

    /**
     * @brief slot_startTraining starts training when triggered.
     */
    void slot_startTraining();

    /**
     * @brief slot_abortTraining tries to stop training when triggered.
     */
    void slot_abortTraining();

    /**
     * @brief slot_results
     */
    void slot_results();

    /**
     * @brief slot_trainingResultUpdated
     */
    void slot_trainingResultUpdated();

    /**
     * @brief slot_classificationResultUpdated
     */
    void slot_classificationResultUpdated();

    /**
     * @brief slot_startClassify starts classification when triggered.
     * @param path
     */
    void slot_startClassify(QString path);

    /**
     * @brief slot_abortClassify tries to stop classification when triggered.
     */
    void slot_abortClassify();

    /**
     * @brief slot_showAugmentationPreview
     */
    void slot_showAugmentationPreview();


    /**
     * @brief slot_modelLoaded called when a model is loaded and UI elements have to update accordingly
     */
    void slot_modelLoaded();

private:
    DataManager *mDataManager;
    InputImagesWidget *mInputImagesWidget;
    AITrainingWidget *mAiTrainingWidget;
    Trainer* mTrainer;
    Classifier* mClassifier;
    QString mTrainingPath;
    QString mClassificationPath;
};

#endif // AICONTROLLER_H
