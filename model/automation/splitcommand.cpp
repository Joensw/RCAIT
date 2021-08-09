#include "splitcommand.h"

SplitCommand::SplitCommand(QString tempPath, QString dataSetpath, int split, ProgressablePlugin *receiver)
{
    connect(this, &SplitCommand::sig_progress, receiver, &Progressable::slot_makeProgress);
    mSplit = split;
    mTempPath = tempPath;
    mDataSetPath = dataSetpath;
    mImageModel = new ImageInspectionModel();
}

bool SplitCommand::execute()
{
    mImageModel->loadDataSet(mDataSetPath);
    mImageModel->loadNewData(mTempPath, mSplit);
    mImageModel->mergeDataSets();
    delete mImageModel;
    emit sig_progress(100);
    return true;
}
