#ifndef IMAGELOADCOMMAND_H
#define IMAGELOADCOMMAND_H

#include "command.h"

#include <imagesearchthread.h>



class ImageLoadCommand : public Command
{
public:
    ImageLoadCommand(QVariantMap map, Progressable* receiver);
    bool execute() override;

private:
    ImageSearchThread* mImageSearcher;
    bool parsingFailed = false;

};

#endif // IMAGELOADCOMMAND_H
