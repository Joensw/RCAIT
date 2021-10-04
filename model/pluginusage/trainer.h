#ifndef TRAINER_H
#define TRAINER_H

#include <trainingresult.h>
#include <qfuturewatcher.h>
#include <classificationpluginmanager.h>
#include <progressableplugin.h>

/**
 * @brief The Trainer class is used to start a training and handle incoming results
 *
 */
class Trainer : public ProgressablePlugin
{
    Q_OBJECT

public:

    /**
     * @brief Trainer constructs Trainer
     *
     */
    Trainer();

    /**
     * @brief classify starts classification in new thread with the given arguments
     *
     * @param pluginName name of selected plugin
     * @param modelName name of selected model
     * @param trainDatasetPath path of dataset used for training
     * @param validationDatasetPath path of dataset used for validation
     * @param workingDirectory model working dir
     */
    void train(const QString &pluginName, const QString &modelName, const QString &trainDatasetPath, const QString &validationDatasetPath, const QString &workingDirectory);

    /**
     * @brief getAugmentationPreview constructs augmentation images in new thread with the given arguments
     *
     * @param pluginName name of selected plugin
     * @param modelName name of selected model
     * @param inputPath path of images to apply augmentation filters
     * @param targetPath target for constructed images
     * @param amount number of constructed images
     */
    void getAugmentationPreview(const QString& pluginName, const QString& modelName, const QString& inputPath, const QString& targetPath, int amount);

    /**
     * @brief getRecentWorkingDir gets latest working directory
     *
     * @return path of latest working directory
     */
    QString getRecentWorkingDir();


signals:

    /**
     * @brief sig_trainingResultUpdated signals new training result
     *
     * @param trainingResult new training result
     */
    void sig_trainingResultUpdated(TrainingResult *trainingResult);

    /**
     * @brief sig_startTraining signals start of training
     *
     */
    void sig_startTraining();

    /**
     * @brief sig_augmentationPreviewReady signals completion of augmentation preview
     *
     * @param success true if augmentation was successful
     * @param targetpath path of augmentation images
     */
    void sig_augmentationPreviewReady(bool success, QString targetpath);

public slots:

    /**
     * @brief slot_handleTrainingsResult is used to handle new training results
     *
     */
    void slot_handleTrainingsResult();

    /**
     * @brief slot_handleAugmentationResult is used to handle new augmentation results
     *
     */
    void slot_handleAugmentationResult();

    /**
     * @brief slot_makeProgress is called when classification made progress
     *
     * @param progress number in percent
     */
    void slot_makeProgress(int progress) override;

private:
    ClassificationPluginManager& mManager = ClassificationPluginManager::getInstance();
    QString mRecentWorkingDir;
    QString mRecentTargetPath;
    QFuture<TrainingResult *> m_trainingResult;
    QFuture<bool> mAugmentationSuccess;



};

#endif // TRAINER_H
