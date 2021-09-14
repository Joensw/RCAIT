#ifndef CLASSIFICATIONCOMMAND_H
#define CLASSIFICATIONCOMMAND_H

#include "command.h"

#include <classificationpluginmanager.h>
#include <progressableplugin.h>

/**
 * @brief The ClassificationCommand class starts a classification with information derived from a map.
 *
 */
class ClassificationCommand : public Command
{
    Q_OBJECT
public:

    /**
     * @brief ClassificationCommand constructs a ClassificationCommand by parsing from a map.
     *
     * @param map contains necessary information for command.
     * @param trainDataSetPath path of training images
     * @param workingDir working directory path
     * @param receiver object to receive progress.
     */
    ClassificationCommand(QVariantMap map, const QString &trainDataSetPath, const QString &workingDir, ProgressablePlugin* receiver);

    /**
     * @brief execute executes the command.
     *
     * @return true if execution was possible (no parsing error).
     */
    bool execute() override;

signals:

    /**
     * @brief sig_saveResult emitted when classification results are ready.
     *
     * @param result classification result.
     */
    void sig_saveResult(ClassificationResult *result);

    /**
     * @brief sig_createLoadModel signals need to load/create model
     *
     * @param modelName name of model
     * @param pluginName name of plugin
     * @param baseModel name of base model
     */
    void sig_createLoadModel(const QString &modelName, const QString &pluginName, const QString &baseModel = QString());


private:
   ClassificationPluginManager& mPluginManager =  ClassificationPluginManager::getInstance();
   ClassificationResult* mResult;
   ProgressablePlugin* mReceiver;
   bool parsingFailed = false;

   QString mImagePath;
   QString mModelName;
   QString mAiPluginName;
   QString mTrainDataSetPath;
   QString mWorkingDir;



};

#endif // CLASSIFICATIONTASK_H
