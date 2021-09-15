#ifndef TRAININGCOMMAND_H
#define TRAININGCOMMAND_H

#include "command.h"


#include <classificationpluginmanager.h>
#include <datamanager.h>
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
     * @param trainDataSetPath
     * @param validationDataSetPath
     * @param workingDir working dir path
     * @param receiver object to receive progress.
     */
    TrainingCommand(QVariantMap map, const QString &trainDataSetPath, const QString &validationDataSetPath, const QString &workingDir, ProgressablePlugin* receiver);

    /**
     * @brief execute executes the command.
     *
     * @return true if execution was possible (no parsing error).
     */
    bool execute() override;

signals:

    /**
     * @brief sig_saveResult emitted when training results are ready.
     *
     * @param result training result.
     */
    void sig_saveResult(TrainingResult *result);

private:

    ClassificationPluginManager& mPluginManager =  ClassificationPluginManager::getInstance();
    DataManager& mDataManager = DataManager::getInstance();
    TrainingResult* mResult;
    ProgressablePlugin* mReceiver;
    QVariantMap mInputOptions;
    QWidget* mInputWidget;
    QVariantMap mAugmentationOptions;
    QWidget* mAugmentationWidget;
    bool parsingFailed = false;

    QString mProjectName;
    QString mImagePath;
    QString mModelName;
    QString mBaseModel;
    QString mAiPluginName;
    QString mTrainDataSetPath;
    QString mValidationDataSetPath;
    QString mClassificationDataSetPath;
    QString mWorkingDir;
};

#endif // TRAININGTASK_H
