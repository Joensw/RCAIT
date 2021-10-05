/**
 * @file imageinspectionmodel.cpp
 *
 * @brief functions for managing a classification dataset on disk
 *
 * @author Sascha Rolinger
 */
#include "imageinspectionmodel.h"

/**
 * @brief This enum maps the index of the dataset type used for input parameters of public functions to a name
 *
 */
enum DataSetType {
    TRAINING_SET = 3,
    VALIDATION_SET = 2,
    TRAINING_NEW = 1,
    VALIDATION_NEW = 0
};


void ImageInspectionModel::loadDataSet(const QString &trainingPath, const QString &validationPath) {
    //reset maps
    m_trainDataset.clear();
    m_validationDataset.clear();

    //add items
    insertLabeledImagePaths(m_trainDataset, trainingPath);
    insertLabeledImagePaths(m_validationDataset, validationPath);

}

void ImageInspectionModel::mergeDataSets(const QString &trainingPath, const QString &validationPath) {
    mergeMap(m_trainDataset, m_trainNewData);
    mergeMap(m_validationDataset, m_validationNewData);

    //move files since we can do it here for free before cleaning up the data structures
    for (const auto &[label, values]: MapAdapt(m_trainNewData)) {
        QStringList dataPaths = {QDir(trainingPath).absoluteFilePath(label),
                                 QDir(validationPath).absoluteFilePath(label)};
        int fileNumber = getFreeImageNumber(dataPaths, label);

        for (const auto &imagePath: values)
            moveFile(imagePath, label, trainingPath, fileNumber++);
    }

    for (const auto &[label, values]: MapAdapt(m_validationNewData)) {
        QStringList dataPaths = {QDir(trainingPath).absoluteFilePath(label),
                                 QDir(validationPath).absoluteFilePath(label)};
        int fileNumber = getFreeImageNumber(dataPaths, label);

        for (const auto &imagePath: values)
            moveFile(imagePath, label, validationPath, fileNumber++);
    }

    m_trainNewData.clear();
    m_validationNewData.clear();
}

void
ImageInspectionModel::mergeMap(const QMap<QString, QStringList> &mergeIn, const QMap<QString, QStringList> &mergeFrom) {
    for (const auto &[label, value]: MapAdapt(mergeFrom))
        mergeIn[label] << value;
}


void ImageInspectionModel::removeImage(int selectionIndex,
                                       const QMap<QString, QList<int>> &removedImages) {
    switch (selectionIndex) {
        case VALIDATION_SET:
            removeImageWithIndex(m_validationDataset, removedImages);
            break;
        case TRAINING_SET:
            removeImageWithIndex(m_trainDataset, removedImages);
            break;
        case VALIDATION_NEW:
            removeImageWithIndex(m_validationNewData, removedImages);
            break;
        case TRAINING_NEW:
            removeImageWithIndex(m_trainNewData, removedImages);
            break;
        default:
            qWarning() << "Unknown selectionIndex: " << selectionIndex;
    }
}

void ImageInspectionModel::loadNewData(const QString &path, int split) {
    //reset maps because new data is coming
    m_trainNewData.clear();
    m_validationNewData.clear();

    //create a temporary map to calculate split for train and validate
    QMap<QString, QStringList> allData;
    insertLabeledImagePaths(allData, path);

    for (const auto &[key, data]: MapAdapt(allData)) {
        qDebug() << key;
        auto dataPoints = data.count();
        double splitPerc = split / 100.0;
        long double splitPosDbl = (long double) dataPoints * splitPerc;
        //we use floor and use the split for train images so validation is not empty except if 100 is chosen
        auto splitPos = (long long int) floorl(splitPosDbl);

        Q_ASSERT(splitPos >= 0 && splitPos <= dataPoints);
        auto trainData = data.sliced(splitPos);
        auto validationData = data.sliced(0, splitPos);
        m_trainNewData[key] = trainData;
        m_validationNewData[key] = validationData;

    }

}

QStringList ImageInspectionModel::readLabeledFolder(const QDir &labeledFolder) {
    QStringList images;
    for (const auto &info: labeledFolder.entryInfoList(QDir::Files)) {
        images << info.absoluteFilePath();
    }

    return images;
}

void ImageInspectionModel::insertLabeledImagePaths(QMap<QString, QStringList> &insertTarget,
                                                   const QString &labeledImagePath) {

    QDir labeledImages(labeledImagePath);
    labeledImages.setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    QDirIterator it(labeledImages, QDirIterator::NoIteratorFlags);

    for (const auto &item: labeledImages.entryInfoList()) {
        if (QDir currDir(item.absoluteFilePath()); currDir.exists() && currDir.isEmpty()) {
            currDir.removeRecursively();
            continue;
        }
        insertTarget.insert(item.fileName(), readLabeledFolder(item.absoluteFilePath()));
    }
}

void ImageInspectionModel::removeImageWithIndex(QMap<QString, QStringList> &removeTarget,
                                                const QMap<QString, QList <int>> &removedImages) {

    for (const auto &[label, values]: MapAdapt(removedImages)) {
           if (values.isEmpty()) {
               continue;
           }
           //iterate from front to back, so we delete images with the largest index first.
           //otherwise, the removetarget indices are reduced by one after the deleted index
           //and our next deletion will not hit the correct filepath in the removetarget
           QListIterator<int> iter(values);
           iter.toBack();
           while (iter.hasPrevious()) {
               int i = iter.previous();
               QFile file(removeTarget[label][i]);
               QDir currDir = QFileInfo(file).absoluteDir();
               auto newList = removeTarget[label];
               newList.removeAt(i);
               removeTarget[label] = newList;
               file.remove();
               if (currDir.exists() && currDir.isEmpty()) {
                   currDir.removeRecursively();
               }
           }
       }

}
const QMap<QString, QStringList> &ImageInspectionModel::getValidationDataset() const {
    return m_validationDataset;
}

const QMap<QString, QStringList> &ImageInspectionModel::getTrainDataset() const {
    return m_trainDataset;
}

const QMap<QString, QStringList> &ImageInspectionModel::getValidationNewData() const {
    return m_validationNewData;
}

const QMap<QString, QStringList> &ImageInspectionModel::getTrainNewData() const {
    return m_trainNewData;
}

void ImageInspectionModel::moveFile(const QString &imagePath, const QString &label, const QString &trainOrValidate,
                                    int fileNumber) {
    QFile file(imagePath);
    QFileInfo fileInfo(file);
    QString suffix = fileInfo.completeSuffix();
    QDir folder(fileInfo.absoluteDir());

    auto dir = QDir(trainOrValidate);

    if (!dir.exists(label)) { dir.mkpath(label); }
    dir.cd(label);
    auto newFile = QString("%1_%2.%3").arg(label, QString::number(fileNumber), suffix);
    auto newFilePath = dir.absoluteFilePath(newFile);
    QFile destFile(newFilePath);

    destFile.remove();
    if (!file.rename(newFilePath)) { qDebug() << "Error moving file: " << file.error(); }
    if (folder.isEmpty()) { folder.removeRecursively(); }

}

int ImageInspectionModel::getFreeImageNumber(const QStringList &paths, const QString &label) {
    static QRegularExpression re("\\d+");
    int res = 1;
    QStringList fileList;
    for (const QString &path: paths) {
        QDir dir(path);
        dir.setNameFilters({label + "_*"});
        fileList << dir.entryList();
    }

    if (fileList.empty()) { return res; }

    std::sort(fileList.begin(), fileList.end(), compareNames);
    if (auto match = re.match(fileList.last()); match.hasMatch()) {
        bool ok;
        QString matched = match.captured(0);
        int lastNumber = matched.toInt(&ok, 10);
        if (ok) { res = ++lastNumber; }
    }

    return res;
}

bool ImageInspectionModel::compareNames(const QString &s1, const QString &s2) {


    QRegularExpressionMatch match1 = REGEX.match(s1);
    QRegularExpressionMatch match2 = REGEX.match(s2);
    int matched1Number = 0;
    int matched2Number = 0;
    if (match1.hasMatch()) {
        QString matched1 = match1.captured(0);
        matched1Number = matched1.toInt();
    }

    if (match2.hasMatch()) {
        QString matched2 = match2.captured(0);
        matched2Number = matched2.toInt();
    }

    return matched1Number < matched2Number;
}


ImageInspectionModel::ImageInspectionModel() = default;
