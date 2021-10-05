#ifndef SPLITCOMMAND_H
#define SPLITCOMMAND_H

#include <command.h>
#include <imageinspectionmodel.h>
#include <progressableplugin.h>
#include <utility>
#include <datamanager.h>

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
     * @param map map with split info
     * @param receiver rececives progress
     */
    SplitCommand(const QVariantMap &map, ProgressablePlugin *receiver);


    /**
     * @brief execute executes the command.
     *
     * @return true if execution was successful.
     */
    bool execute() override;

    /**
     * @brief default destructor for SplitCommand class
     *
     */
    virtual ~SplitCommand() = default;

signals:

    /**
     * @brief sig_progress signals progress
     * @param progress progress in percent
     */
    void sig_progress(int progress);

private:
    int mSplit = 40;
    DataManager &mDataManager = DataManager::getInstance();
    QString mTempPath;
    QString mTrainPath;
    QString mValidationPath;
    QScopedPointer<ImageInspectionModel> mImageModel;
};

#endif // SPLITCOMMAND_H
