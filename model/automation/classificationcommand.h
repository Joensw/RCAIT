#ifndef CLASSIFICATIONCOMMAND_H
#define CLASSIFICATIONCOMMAND_H

#include "command.h"

#include <classificationpluginmanager.h>
#include <datamanager.h>
#include <progressableplugin.h>
#include <utility>

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
     * @param receiver object to receive progress.
     */
    ClassificationCommand(QVariantMap map, ProgressablePlugin *receiver);

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
    void sig_saveResult(QSharedPointer<ClassificationResult> result);

private:

    ClassificationPluginManager &mPluginManager = ClassificationPluginManager::getInstance();
    DataManager &mDataManager = DataManager::getInstance();
    QSharedPointer<ClassificationResult> mResult{};
    bool parsingFailed = false;

    QString mProjectName;
    QString mImagePath;
    QString mModelName;
    QString mAiPluginName;
    QString mTrainDataSetPath;
    QString mWorkingDir;
    ProgressablePlugin *mReceiver;

};

#endif // CLASSIFICATIONCOMMAND_H
