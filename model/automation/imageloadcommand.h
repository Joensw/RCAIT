#ifndef IMAGELOADCOMMAND_H
#define IMAGELOADCOMMAND_H

#include "command.h"

#include <imagesearchthread.h>


/**
 * @brief The ImageLoadCommand class starts image loading with information derived from a map.
 *
 */
class ImageLoadCommand : public Command
{
public:

    /**
     * @brief ImageLoadCommand constructs a ImageLoadCommand by parsing from a map.
     *
     * @param map contains necessary information for command.
     * @param receiver object to receive progress.
     */
    ImageLoadCommand(QVariantMap map, Progressable* receiver);

    /**
     * @brief execute executes the command.
     *
     * @return true if execution was possible (no parsing error).
     */
    bool execute() override;

private:
    ImageSearchThread* mImageSearcher;
    bool parsingFailed = false;

};

#endif // IMAGELOADCOMMAND_H
