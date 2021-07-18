#ifndef ADDPROJECTCOMMAND_H
#define ADDPROJECTCOMMAND_H

#include "command.h"


// never used, remove later
class AddProjectCommand : public Command
{
public:
    AddProjectCommand(QVariantMap map);
    bool execute() override;
};

#endif // ADDPROJECTTASK_H
