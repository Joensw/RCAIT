#include "splitcommand.h"

SplitCommand::SplitCommand(QString tempPath, QString trainPath, QString validationPath, int split, ProgressablePlugin *receiver)
{
    connect(this, &SplitCommand::sig_progress, receiver, &Progressable::slot_makeProgress);
    mSplit = split;
    mTempPath = tempPath;
    mTrainPath = trainPath;
    mValidationPath = validationPath;
    mImageModel.reset(new ImageInspectionModel);
}

bool SplitCommand::execute()
{
    mImageModel->loadNewData(mTempPath, mSplit);
    mImageModel->mergeDataSets(mTrainPath, mValidationPath);
    mImageModel.reset();
    emit sig_progress(100);
    return true;
}
