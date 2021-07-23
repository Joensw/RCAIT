#ifndef CLASSIFICATIONCOMMAND_H
#define CLASSIFICATIONCOMMAND_H

#include "command.h"

#include <classificationthread.h>

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
    ClassificationCommand(QVariantMap map, Progressable* receiver);

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
    void sig_saveResult(ClassificationResult result);

private slots:
     void slot_saveResult();

private:
   ClassificationThread *mClassifier;
   bool parsingFailed = false;



};

#endif // CLASSIFICATIONTASK_H
