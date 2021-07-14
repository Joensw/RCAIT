#ifndef CLASSIFICATIONCOMMAND_H
#define CLASSIFICATIONCOMMAND_H

#include "command.h"

#include <classificationthread.h>

class ClassificationCommand : public Command
{
    Q_OBJECT
public:
    ClassificationCommand(QVariantMap map);
    bool execute() override;

signals:
    void sig_saveResult(ClassificationResult result);

private:
   ClassificationThread *mClassifier;
   QString mProjectName;


};

#endif // CLASSIFICATIONTASK_H
