#include "imageinspectionmodel.h"
#include "model/utilities/mapadapt.h"

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

void ImageInspectionModel::mergeMap(const QMap<QString, QStringList> &mergeIn, const QMap<QString, QStringList> &mergeFrom) {
    for (const auto &[label, value]: MapAdapt(mergeFrom)) {
        if (mergeIn.contains(label))
            mergeIn[label] << value;
        else
            mergeIn[label] = value;
    }
}


void ImageInspectionModel::removeImage(int selectionIndex, const QMap<QString, QList<int>> &removedImages) {
    switch (selectionIndex) {
        case 2:
            removeImageWithIndex(m_validationDataset, removedImages);
        case 3:
            removeImageWithIndex(m_trainDataset, removedImages);
        case 0:
            removeImageWithIndex(m_validationNewData, removedImages);
        case 1:
            removeImageWithIndex(m_trainNewData, removedImages);
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

        Q_ASSERT(splitPos >= 0 && splitPos < dataPoints);
        auto trainData = data.sliced(0, splitPos);
        auto validationData = data.sliced(splitPos);

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

void ImageInspectionModel::insertLabeledImagePaths(const QMap<QString, QStringList> &insertTarget,
                                                   const QString &labeledImagePath) {

    QDir labeledImages(labeledImagePath);
    labeledImages.setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    QDirIterator it(labeledImages, QDirIterator::NoIteratorFlags);

    for (const auto &item: labeledImages.entryInfoList()) {
        auto dir = item.dir();
        insertTarget[dir.dirName()] = readLabeledFolder(dir);
    }
}

void ImageInspectionModel::removeImageWithIndex(const QMap<QString, QStringList> &removeTarget,
                                                const QMap<QString, QList<int>> &removedImages) {

    for (const auto &[label, values]: MapAdapt(removedImages)) {
        for (auto i = values.count() - 1; i >= 0; i--) {
            if (!values.contains(i)) continue;

                QFile file(removeTarget[label][i]);
                auto newList = removeTarget[label];
                newList.removeAt(i);
                removeTarget[label] = newList;
                file.remove();
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
    QString newPath = dir.absoluteFilePath(label);
    if (!dir.exists(label)) { dir.mkpath(label); }
    dir.cd(label);
    auto newFile = QString("%1_%2.%3").arg(label, QString::number(fileNumber), suffix);
    auto newFilePath = dir.absoluteFilePath(newFile);
    QFile destFile(newFilePath);

    if (destFile.exists()) { destFile.remove(); }
    if (!file.rename(newFilePath)) { qDebug() << "Error moving file: " << file.error(); }
    if (folder.isEmpty()) { folder.removeRecursively(); }

}

int ImageInspectionModel::getFreeImageNumber(const QStringList &paths, const QString &label) {
    int res = 1;
    QStringList fileList;
    for (const QString &path: paths) {
        QDir dir(path);
        dir.setNameFilters({label + "_*"});
        fileList << dir.entryList();
    }

    if (fileList.empty()) { return res; }

    std::sort(fileList.begin(), fileList.end(), compareNames);
    QRegularExpression re("\\d+");
    QRegularExpressionMatch match = re.match(fileList.last());
    if (match.hasMatch()) {
        bool ok;
        QString matched = match.captured(0);
        int lastNumber = matched.toInt(&ok, 10);
        if (ok) { res = ++lastNumber; }
    }

    return res;
}

bool ImageInspectionModel::compareNames(const QString &s1, const QString &s2) {

    QRegularExpression re("\\d+");
    QRegularExpressionMatch match1 = re.match(s1);
    QRegularExpressionMatch match2 = re.match(s2);
    int matched1Number = 0;
    int matched2Number = 0;
    if (match1.hasMatch()) {
        QString matched1 = match1.captured(0);
        matched1Number = matched1.toInt(nullptr, 10);
    }

    if (match2.hasMatch()) {
        QString matched2 = match2.captured(0);
        matched2Number = matched2.toInt(nullptr, 10);
    }

    return matched1Number <= matched2Number;
}


