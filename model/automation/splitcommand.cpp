#include "splitcommand.h"

SplitCommand::SplitCommand(QString tempPath, QString trainPath, QString validationPath, int split,
                           ProgressablePlugin *receiver)
        : mSplit(split),
          mTempPath(std::move(tempPath)),
          mTrainPath(std::move(trainPath)),
          mValidationPath(std::move(validationPath)),
          mImageModel(new ImageInspectionModel) {
    connect(this, &SplitCommand::sig_progress, receiver, &Progressable::slot_makeProgress);

}

bool SplitCommand::execute() {
    mImageModel->loadNewData(mTempPath, mSplit);
    mImageModel->mergeDataSets(mTrainPath, mValidationPath);
    emit sig_progress(100);
    return true;
}
