#ifndef IMAGELOADCOMMAND_H
#define IMAGELOADCOMMAND_H

#include "command.h"
#include <mapadapt.h>

#include <imageloaderpluginmanager.h>


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
     * @param imagePath load pictures into path.
     * @param receiver object to receive progress.
     */
    ImageLoadCommand(QVariantMap map, const QString &imagePath, ProgressablePlugin *receiver);

    /**
     * @brief execute executes the command.
     *
     * @return true if execution was possible (no parsing error).
     */
    bool execute() override;

private:
    ImageLoaderPluginManager& mPluginManager =  ImageLoaderPluginManager::getInstance();
    ProgressablePlugin* mReceiver;
    QVariantMap mWidgetOptions;
    QSharedPointer<QWidget> mInputWidget;
    bool parsingFailed = false;
    int mCount;
    QStringList mLabels;
    QString mPluginName;
    QString mPath;

};

#endif // IMAGELOADCOMMAND_H
