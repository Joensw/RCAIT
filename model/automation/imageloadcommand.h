#ifndef IMAGELOADCOMMAND_H
#define IMAGELOADCOMMAND_H

#include "command.h"



class ImageLoadCommand : public Command
{
public:
    ImageLoadCommand(QVariantMap map);
    bool execute() override;
};

#endif // IMAGELOADCOMMAND_H
