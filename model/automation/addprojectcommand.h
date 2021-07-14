#ifndef ADDPROJECTCOMMAND_H
#define ADDPROJECTCOMMAND_H

#include "command.h"

class AddProjectCommand : public Command
{
public:
    AddProjectCommand(QVariantMap map);
    void execute() override;
};

#endif // ADDPROJECTTASK_H
