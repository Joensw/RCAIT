#ifndef CLASSIFICATIONCOMMAND_H
#define CLASSIFICATIONCOMMAND_H

#include "command.h"

class ClassificationCommand : public Command
{
public:
    ClassificationCommand(QVariantMap map);

private:
   // ClassificationThread *mTrainer;
};

#endif // CLASSIFICATIONTASK_H
