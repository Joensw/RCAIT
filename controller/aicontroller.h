/**
 * @file aicontroller.h
 *
 * @brief connects the ai classification and training logic with the user interface
 *
 * @author Andreas Ott
 */
#ifndef AICONTROLLER_H
#define AICONTROLLER_H

#include <QString>
#include <aitrainingwidget.h>
#include <datamanager.h>
#include <inputimageswidget.h>
#include <classifier.h>
#include <trainer.h>
#include <resultscontroller.h>
#include "imagegallery.h"
/**
 * @brief The AIController class mediates between ui elements and classification/training.
 */
class AIController final : public QObject

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

    /**
     * @brief operator = deleted assignment operator
     * @return
     */
    AIController &operator=(const AIController &) = delete;

public slots:

    /**
     * @brief slot_startTraining starts training when triggered.
     */
    void slot_startTraining();

    /**
     * @brief sig_trainingResultUpdated can be called when a new training result is available
     * @param trainingResult is the result of the last executed training
     */
    void slot_trainingResultUpdated(const QPointer<TrainingResult> &trainingResult);

    /**
     * @brief sig_classificationResultUpdated can be called when a new classification result is available
     * @param classificationResult is the result of the last executed classification
     */
    void slot_classificationResultUpdated(const QPointer<ClassificationResult> &classificationResult);

    /**
     * @brief slot_startClassify starts classification when triggered.
     * @param path
     */
    void slot_startClassify(const QString &path);

    /**
     * @brief slot_showAugmentationPreview loads augmentation preview when triggered.
     * @param amount number of new images
     */
    void slot_showAugmentationPreview(int amount);


    /**
     * @brief slot_modelLoaded called when a model is loaded and UI elements have to update accordingly
     */
    void slot_modelLoaded();

    /**
     * @brief slot_automationPreviewReady
     * @param success
     */
    void slot_augmentationPreviewReady(bool success, const QString &targetPath);
signals:

    /**
     * @brief sig_trainingResultUpdated emitted when a new training result is available
     * @param trainingResult is the result of the last executed training
     */
    void sig_trainingResultUpdated(const QPointer<TrainingResult> &trainingResult);

    /**
     * @brief sig_classificationResultUpdated emitted when a new classification result is available
     * @param classificationResult is the result of the last executed classification
     */
    void sig_classificationResultUpdated(const QPointer<ClassificationResult> &classificationResult);

private:
    DataManager *mDataManager;
    InputImagesWidget *mInputImagesWidget;
    AITrainingWidget *mAiTrainingWidget;
    QScopedPointer<Trainer> mTrainer;
    QScopedPointer<Classifier> mClassifier;
    QString mTrainingPath;
    QString mClassificationPath;
    bool mPluginInUse = false;
};

#endif // AICONTROLLER_H
