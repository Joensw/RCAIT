#ifndef TRAININGCOMMAND_H
#define TRAININGCOMMAND_H

#include "command.h"

#include <pluginusage/trainingsthread.h>

#include <classificationpluginmanager.h>
#include <progressableplugin.h>


/**
 * @brief The TrainingCommand class starts a training with information derived from a map.
 */
class TrainingCommand : public Command
{
    Q_OBJECT
public:

    /**
     * @brief TrainingCommand constructs a TrainingCommand by parsing from a map.
     *
     * @param map contains necessary information for command.
     * @param receiver object to receive progress.
     */
    TrainingCommand(QVariantMap map, QString trainDataSetPath, QString validationDataSetPath, QString workingDir, ProgressablePlugin* receiver);

    /**
     * @brief execute executes the command.
     *
     * @return true if execution was possible (no parsing error).
     */
    bool execute() override;

signals:

    /**
     * @brief sig_saveResult emitted when training results are ready.
     * @param result training result.
     */
    void sig_saveResult(TrainingResult *result);

private slots:
    void slot_saveResult();

private:
    ClassificationPluginManager& mPluginManager =  ClassificationPluginManager::getInstance();
    TrainingResult* mResult;
    ProgressablePlugin* mReceiver;
    bool parsingFailed = false;

    QString mImagePath;
    QString mModelName;
    QString mAiPluginName;
    QString mTrainDataSetPath;
    QString mValidationDataSetPath;
    QString mClassificationDataSetPath;
    QString mWorkingDir;





};

#endif // TRAININGTASK_H
