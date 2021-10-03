#include "splitcommand.h"

SplitCommand::SplitCommand(const QVariantMap &map, ProgressablePlugin *receiver)
        : mTempPath(mDataManager.getProjectImageTempDir()),
          mTrainPath(mDataManager.getProjectDataSetTrainSubdir()),
          mValidationPath(mDataManager.getProjectDataSetValSubdir()),
          mImageModel(new ImageInspectionModel) {
    bool ok;
    int split = map["split"].toInt(&ok);
    if (ok && split > 0 && split < 100) mSplit = split;
    connect(this, &SplitCommand::sig_progress, receiver, &Progressable::slot_makeProgress);
}

bool SplitCommand::execute() {
    mImageModel->loadNewData(mTempPath, mSplit);
    mImageModel->mergeDataSets(mTrainPath, mValidationPath);
    emit sig_progress(100);
    return true;
}
