#ifndef CLASSIFICATIONCOMMAND_H
#define CLASSIFICATIONCOMMAND_H

#include "command.h"

#include <classificationpluginmanager.h>
#include <classificationthread.h>
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
     * @param result classification result.
     */
    void sig_saveResult(ClassificationResult *result);


private:
   ClassificationPluginManager& mPluginManager =  ClassificationPluginManager::getInstance();
   ClassificationResult* mResult;
   ProgressablePlugin* mReceiver;
   QVariantMap mWidgetOptions;
   QWidget* mInputWidget;
   bool parsingFailed = false;

   QString mImagePath;
   QString mModelName;
   QString mAiPluginName;
   QString mTrainDataSetPath;
   QString mWorkingDir;



};

#endif // CLASSIFICATIONTASK_H
