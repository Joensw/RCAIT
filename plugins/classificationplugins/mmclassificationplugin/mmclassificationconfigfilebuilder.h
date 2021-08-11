#ifndef MMCLASSIFICATIONCONFIGFILEBUILDER_H
#define MMCLASSIFICATIONCONFIGFILEBUILDER_H

#include <QString>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QRegularExpression>

class MMClassificationConfigFileBuilder
{
public:
    MMClassificationConfigFileBuilder();
    void setPathToMMClassification(QString pathToMMClassification);

    QString createDatasetFileForDataAugmentationPreviewConfigFile();
    QString createMainConfigFile(QString name, QString modelConfigPath, QString datasetConfigPath, QString scheduleConfigPath, QString runtimeConfigPath, QString checkpointName);
    QString createModelConfigFile(QString name, QString baseModelPath);
    QString createDatasetConfigFile(QString name);
    QString createScheduleConfigFile(QString name);
    QString createRuntimeConfigFile(QString name);

    QString getDefaultRuntimeConfigFilePath();

    void changeRuntimeConfigPathInMainConfig(QString mainConfigPath, QString newRuntimeConfigPath);
    void changeCheckpointFilePath(QString mainConfigPath, QString checkpointFilePath);
    void changeModelNumberOfClasses(QString modelConfigPath, int numberOfClasses);
    void changeDataAugmentationOptions(QString datasetConfigPath, QString albuTransform, int randomResizedCropSize, double randomFlipProb, QString randomFlipDirection, bool RandomErasing, int resize, int centerCropSize);
    void changeDatasetPaths(QString datasetConfigPath, QString trainingSetPath, QString validatinoSetPath, QString testSetPath);
    void changeTestPath(QString datasetConfigPath, QString testSetPath);
    void changeScheduleOptions(QString scheduleConfigPath, int maxIterations);
    void changeCheckpointCreationStep(QString runtimeConfigPath, int step);

    QStringList readFileLines(QString pathToFile); // -> zu private
    bool readAndReplaceLinesInOrder(QString pathToFile, QVector<QString> regularExpressions, QVector<QString> replaceWith, int caputureGroupIndex);
    void writeBack(QString pathToFile, QStringList data);
    QString replaceText(QString data, QString regularExpressionText, int captureGroupIndex, QString replacementText);

private:

    QString createConfigFile(QString name, QString defaultFilePath);
    //QString m_pathToMMClassification = "C:\\Users/Informatik/mmclassification"; // fester Wert nur für Testzwecke !!!!!!
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
