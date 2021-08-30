#ifndef MMCLASSIFICATIONCONFIGFILEBUILDER_H
#define MMCLASSIFICATIONCONFIGFILEBUILDER_H

#include <QString>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QRegularExpression>

/**
 * @brief The MMClassificationConfigFileBuilder class can create and change config files using default config files and the config include hierarchy of the MMClassification repository
 */
class MMClassificationConfigFileBuilder
{
public:
    /**
     * @brief MMClassificationConfigFileBuilder creates a new instance of this class
     */
    MMClassificationConfigFileBuilder();

    /**
     * @brief setPathToMMClassification sets the path to the mmclassification repository directory containing the config subfolder
     * @param pathToMMClassification the absolute path to mmclassification or another directory containing the config hierarchy and the default configs
     */
    void setPathToMMClassification(QString pathToMMClassification);

    /**
     * @brief createDatasetFileForDataAugmentationPreviewConfigFile creates a seperate dataset config file to seperate the changes made by the preview
     * @return the path of the created dataset config file for the preview
     */
    QString createDatasetFileForDataAugmentationPreviewConfigFile();

    /**
     * @brief createMainConfigFile creates a new main config file including the associated config files and specifying the checkpoint file
     * @param name to identy the main config file
     * @param modelConfigPath the path of the model config file
     * @param datasetConfigPath the path of the dataset config file
     * @param scheduleConfigPath the path of the schedule config file
     * @param runtimeConfigPath the path of the runtime config file
     * @param checkpointName the name of the checkpoint file to start with
     * @return the path of the created main config file
     */
    QString createMainConfigFile(const QString& name, const QString& modelConfigPath, const QString& datasetConfigPath, const QString& scheduleConfigPath, const QString& runtimeConfigPath, const QString& checkpointName);

    /**
     * @brief createModelConfigFile creates a new model config file by copying the default_model.py file in configs/_base_/models
     * @param name to identify the model config file
     * @param baseModelPath the path to the config of the base model
     * @return the path of the created model config file
     */
    QString createModelConfigFile(const QString& name, const QString& baseModelPath);

    /**
     * @brief createDatasetConfigFile creates a new dataset config file by copying the default_dataset.py file in configs/_base_/datasets
     * @param name to identify the dataset config file
     * @return the path of the created dataset config file
     */
    QString createDatasetConfigFile(const QString& name);

    /**
     * @brief createScheduleConfigFile creates a new schedule config file by copying the default_schedule.py file in configs/_base_/schedules
     * @param name to identify the dataset config file
     * @return the path of the created schedule config file
     */
    QString createScheduleConfigFile(const QString& name);

    /**
     * @brief createRuntimeConfigFile creates a new runtime config file by copying the default_runtime.py file in configs/_base_
     * @param name to identify the runtime config file
     * @return the path of the created runtime config file
     */
    QString createRuntimeConfigFile(const QString& name);

    /**
     * @brief getDefaultRuntimeConfigFilePath returns the path to the default_runtime.py file in configs/_base_ as it is sufficient for many cases
     * @return path to the default_runtime.py file
     */
    QString getDefaultRuntimeConfigFilePath();

    /**
     * @brief changeRuntimeConfigPathInMainConfig changes the path of the runtime config file in the given main config file
     * @param mainConfigPath the path to the main config file, which should use the given runtime config
     * @param newRuntimeConfigPath the path to the new runtime config
     */
    void changeRuntimeConfigPathInMainConfig(const QString& mainConfigPath, const QString& newRuntimeConfigPath);

    /**
     * @brief changeCheckpointFilePath changes the path of the checkpoint file in the given main config file
     * @param mainConfigPath the path to the main config file, which should use the given checkpoint file
     * @param checkpointFilePath the path to the new checkpoint file
     */
    static void changeCheckpointFilePath(const QString& mainConfigPath, const QString& checkpointFilePath);

    /**
     * @brief changeModelNumberOfClasses changes the number of classes specification in the model config file
     * @param modelConfigPath the path to the modelConfigFile, where the number of classes should be changed
     * @param numberOfClasses a postive integer value, specifying the number of classes of the dataset
     */
    void changeModelNumberOfClasses(const QString& modelConfigPath, qsizetype numberOfClasses);

    /**
     * @brief changeDataAugmentationOptions changes data augmentation parameter in the dataset config file
     * @param datasetConfigPath the path of the dataset file to be changed
     * @param albuTransform the name of an transform type of Albumentations
     * @param randomResizedCropSize the size to which the input pictures will be cropped
     * @param randomFlipProb probability of a random flip of an input picture
     * @param randomFlipDirection the direction in which the input pictures will be rotated
     * @param RandomErasing option to activate (true) or deactivate (false) random erasing
     * @param resize the size to resize the input pictures
     * @param centerCropSize size of the from center cropped pictures
     */
    static void changeDataAugmentationOptions(const QString& datasetConfigPath, const QString& albuTransform, int randomResizedCropSize, double randomFlipProb, const QString& randomFlipDirection, bool RandomErasing, int resize, int centerCropSize);

    /**
     * @brief changeDatasetPaths changes the absolute paths of the train, validation and test dataset in the given dataset config
     * @param datasetConfigPath the path of the dataset config file to be changed
     * @param trainingSetPath the absolute path of the training dataset
     * @param validatinoSetPath the absolute path of the validation dataset
     * @param testSetPath the absolute path of the test dataset
     */
    void changeDatasetPaths(const QString& datasetConfigPath, const QString& trainingSetPath, const QString& validatinoSetPath, const QString& testSetPath);

    /**
     * @brief changeTestPath changes the test dataset path in the given dataset config file
     * @param datasetConfigPath the dataset config file to be changed
     * @param testSetPath the new absolute path of test dataset
     */
    void changeTestPath(const QString& datasetConfigPath, const QString& testSetPath);

    /**
     * @brief changeScheduleOptions changes the maximal number of iterations and thereby the associated step size in the given schedule config
     * @param scheduleConfigPath the path to the schedule config file to be changed
     * @param maxIterations the maximal number of iterations during a training
    */
    void changeScheduleOptions(const QString& scheduleConfigPath, int maxIterations);

    /**
     * @brief changeCheckpointCreationStep changes the size of the checkpoint creation step in the given runtime config
     * @param runtimeConfigPath the runtime config to be changed
     * @param step determines after how many iterations a new checkpoint file is created
     */
    void changeCheckpointCreationStep(const QString& runtimeConfigPath, int step);

private:

    QString createConfigFile(const QString& name, const QString& defaultFilePath);
    static QStringList readFileLines(const QString& pathToFile);
    static bool readAndReplaceLinesInOrder(const QString& pathToFile, QVector<QString> regularExpressions, QVector<QString> replaceWith, int caputureGroupIndex);
    static void writeBack(const QString& pathToFile, const QStringList& data);
    static QString replaceText(QString data, const QString& regularExpressionText, int captureGroupIndex, const QString& replacementText);

    QString m_pathToMMClassification = "";

    QString m_subFolderConfigs = "configs";
    const QString m_subfolderCheckpoints = "checkpoints";

    const QString m_defaultModelConfigPath = "configs/_base_/models/default_model.py";
    const QString m_defaultDatasetConfigPath = "configs/_base_/datasets/default_dataset.py";
    const QString m_defaultScheduleConfigPath = "configs/_base_/schedules/default_schedule.py";
    const QString m_defaultRuntimeConfigPath = "configs/_base_/default_runtime.py";

    const QString m_previewConfigPath = "configs/datapreviewConfig.py";

    const QString m_newLineRegExText = "[\r\n]";

    const QString m_runtimeConfigPathRegExText = "_base_ = \\[\\s*'.*'*,\\s*'.*',\\s*'(.*)'";

    const QString m_trainPathRegExText = "train = (.|\n)*data_prefix = (.|\n)*'(.*)',\n.*train_pipeline";
    const QString m_validationPathRegExText = "val = (.|\n)*data_prefix = (.|\n)*'(.*)',(.|\n)*\\),";
    const QString m_testPathRegExText = "test = (.|\n)*data_prefix = (.|\n)*'(.*)',(.|\n)*pipeline";
    const QString m_maxItersRegExText = "max_iters=\\d+";
    const QString m_step = "step=\\[(\\d+)";
    const QString m_checkpointInterval = "checkpoint_config = dict\\(interval=(\\d+)";

};

#endif // MMCLASSIFICATIONCONFIGFILEBUILDER_H
