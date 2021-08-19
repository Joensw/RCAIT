#ifndef SPLITCOMMAND_H
#define SPLITCOMMAND_H

#include "command.h"

#include <imageinspectionmodel.h>
#include <progressableplugin.h>

/**
 * @brief The SplitCommand class splits loaded images between training- and validation-images.
 */
class SplitCommand : public Command
{
    Q_OBJECT
public:
    /**
     * @brief SplitCommand constructs a SplitCommand with given split.
     *
     * @param path path of temp images.
     * @param dataSetPath path of dataset.
     * @param receiver object to receive progress.
     */
    SplitCommand(QString path, QString trainPath, QString validationPath, int split, ProgressablePlugin* receiver);


    /**
     * @brief execute executes the command.
     *
     * @return true if execution was successful.
     */
    bool execute() override;

signals:
    void sig_progress(int progress);

private:
    int mSplit;
    QString mTempPath;
    QString mTrainPath;
    QString mValidationPath;
    ImageInspectionModel* mImageModel;
};

#endif // SPLITCOMMAND_H
