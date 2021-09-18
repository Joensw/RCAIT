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
     * @param tempPath path of temp images.
     * @param dataSetPath path of dataset.
     * @param receiver object to receive progress.
     */
    SplitCommand(const QString &tempPath, const QString &trainPath,  const QString &validationPath, int split, ProgressablePlugin* receiver);


    /**
     * @brief execute executes the command.
     *
     * @return true if execution was successful.
     */
    bool execute() override;

signals:

    /**
     * @brief sig_progress signals progress
     * @param progress progress in percent
     */
    void sig_progress(int progress);

private:
    int mSplit;
    QString mTempPath;
    QString mTrainPath;
    QString mValidationPath;
    QScopedPointer<ImageInspectionModel> mImageModel;
};

#endif // SPLITCOMMAND_H
