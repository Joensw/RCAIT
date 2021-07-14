#ifndef CLASSIFICATIONCOMMAND_H
#define CLASSIFICATIONCOMMAND_H

#include "command.h"

#include <classificationthread.h>

class ClassificationCommand : public Command
{
    Q_OBJECT
public:
    ClassificationCommand(QVariantMap map, Progressable* receiver);
    bool execute() override;

signals:
    void sig_saveResult(ClassificationResult result);

private:
   ClassificationThread *mClassifier;
   bool parsingFailed = false;



};

#endif // CLASSIFICATIONTASK_H
