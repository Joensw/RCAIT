#include "imageinspectionmodel.h"

void ImageInspectionModel::loadDataSet(const QString &trainingPath, const QString &validationPath) {
    //reset maps
    m_trainDataset.clear();
    m_validationDataset.clear();

    //add items
    insertLabeledImagePaths(&m_trainDataset, trainingPath);
    insertLabeledImagePaths(&m_validationDataset, validationPath);

}

void ImageInspectionModel::mergeDataSets(const QString &trainingPath, const QString &validationPath) {
    mergeMap(&m_trainDataset, m_trainNewData);
    mergeMap(&m_validationDataset,m_validationNewData);
    //move files since we can do it here for free before cleaning up the data structures
    foreach(QString label, m_trainNewData.keys()){
        QStringList dataPaths = QStringList() << trainingPath + "/" + label << validationPath + "/" + label;
        int fileNumber = getFreeImageNumber(dataPaths,label);

        for(QString& imagePath : m_trainNewData.value(label)){
            moveFile(imagePath, label, trainingPath, fileNumber);
            fileNumber++;
        }
    }

    foreach(QString label, m_validationNewData.keys()){
        QStringList dataPaths = QStringList() << trainingPath + "/" + label << validationPath + "/" + label;
        int fileNumber = getFreeImageNumber(dataPaths,label);

        for(QString& imagePath : m_validationNewData.value(label)){
            moveFile(imagePath, label, validationPath, fileNumber);
            fileNumber++;
        }
    }

    m_trainNewData.clear();
    m_validationNewData.clear();
}

void ImageInspectionModel::mergeMap(QMap<QString, QStringList> *mergeIn, QMap<QString, QStringList> mergeFrom) {
            foreach(QString label, mergeFrom.keys()){
            if(mergeIn->contains(label)){
                mergeIn->value(label).append(mergeFrom.value(label));
            } else {
                mergeIn->insert(label,mergeFrom.value(label));
            }
        }
}


void ImageInspectionModel::removeImage(int selectionIndex, QMap<QString, QList<int>> removedImages) {
    switch(selectionIndex){
        case 2: removeImageWithIndex(&m_validationDataset,removedImages);
        case 3: removeImageWithIndex(&m_trainDataset,removedImages);
        case 0: removeImageWithIndex(&m_validationNewData,removedImages);
        case 1: removeImageWithIndex(&m_trainNewData,removedImages);
    }

}

void ImageInspectionModel::loadNewData(const QString &path, int split) {
    //reset maps because new data is coming
    m_trainNewData.clear();
    m_validationNewData.clear();

    //create a temporary map to calculate split for train and validate
    QMap<QString, QStringList> allData;
    insertLabeledImagePaths(&allData,path);
    QStringList allDataKeys = allData.keys();

    for(QString& key : allDataKeys){
        qDebug() << key;
        int dataPoints = allData.value(key).count();
        double splitPerc = (double) split/ (double) 100;
        double splitPosDbl = (double) dataPoints * splitPerc;
        //we use floor and use the split for train images so validation is not empty except if 100 is chosen
        int splitPosInt = floor(splitPosDbl);

        QStringList data = allData.value(key);
        QStringList trainData;
        QStringList validationData;
        //put images in train/validation lists depending on split. Could be done with QList.mid but crashes the debugger
        for(int i = 0; i < dataPoints; i++){
            if(i < splitPosInt){
                validationData.append(data.at(i));
            } else {
                trainData.append(data.at(i));
            }
        }

        m_trainNewData.insert(key,trainData);
        m_validationNewData.insert(key,validationData);

    }

}

QStringList ImageInspectionModel::readLabeledFolder(QDir labeledFolder) {
    QFileInfoList files = labeledFolder.entryInfoList(QStringList(), QDir::Files);
    QStringList images;
    for(QFileInfo info : files){
        images.append(info.absoluteFilePath());
    }

    return images;
}

void ImageInspectionModel::insertLabeledImagePaths(QMap<QString, QStringList> *insertTarget, QString labeledImagePath){


    QDir toIterate = QDir(labeledImagePath);
    toIterate.setFilter(QDir::NoDotAndDotDot | QDir::AllEntries); //workaround to filter dot and dotdot because setting flag for iterator itself is bugged
    QDirIterator it(toIterate, QDirIterator::NoIteratorFlags);

    while (it.hasNext()) {
        QDir dir = it.next();
        insertTarget->insert(dir.dirName(),readLabeledFolder(dir));
    }
}

void ImageInspectionModel::removeImageWithIndex(QMap<QString, QStringList> *removeTarget, QMap<QString, QList<int>> removedImages) {
    //ToDo: Implement when view is defined
    //https://doc.qt.io/qt-5/qmap-key-iterator.html
    foreach(QString label, removedImages.keys()){
        for(int i = removeTarget->value(label).count() - 1; i >= 0; i--){
            if(removedImages.value(label).contains(i)){
                QFile file(removeTarget->value(label).at(i));
                QStringList newList = removeTarget->value(label);
                newList.removeAt(i);
                removeTarget->insert(label,newList);
                file.remove();
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

void ImageInspectionModel::moveFile(const QString &imagePath, const QString &label, const QString &trainOrValidate, int fileNumber) {
    QFile file(imagePath);
    QFileInfo fileInfo(file);
    QString suffix = fileInfo.completeSuffix();
    QDir folder(fileInfo.absoluteDir());
    QString filename(fileInfo.fileName()); //never used
    QString newPath = trainOrValidate + "/" + label;
    if(!QDir(newPath).exists()) {
        QDir().mkdir(newPath);
    }
    QString newFileName = newPath + "/" + label + "_" + QString::number(fileNumber) + "." + suffix;
    QFile destFile(newFileName);
    if(destFile.exists()){
        destFile.remove();
    }
    if(!file.rename(newFileName)){
        qDebug() << "Error renaming file";
    }
    if(folder.isEmpty()){
        folder.removeRecursively();
    }

}

int ImageInspectionModel::getFreeImageNumber(const QStringList &paths, const QString &label)
{
    int res = 1;
    QStringList fileList;
    for(QString path : paths){
        QDir dir(path);
        dir.setNameFilters(QStringList()<<label + "_*");
        fileList.append(dir.entryList());
    }

    if(fileList.empty()){
        return res;
    }

    std::sort(fileList.begin(),fileList.end(),compareNames);
    QRegularExpression re("\\d+");
    QRegularExpressionMatch match = re.match(fileList.last());
    if (match.hasMatch()) {
        bool ok;
        QString matched = match.captured(0);
        int lastNumber = matched.toInt(&ok,10);
        if(ok){
            res = lastNumber + 1;
        }
    }

    return res;
}

bool ImageInspectionModel::compareNames(const QString &s1, const QString &s2)
{

    QRegularExpression re("\\d+");
    QRegularExpressionMatch match1 = re.match(s1);
    QRegularExpressionMatch match2 = re.match(s2);
    int matched1Number = 0;
    int matched2Number = 0;
    if (match1.hasMatch()) {
        bool ok;
        QString matched1 = match1.captured(0);
        matched1Number = matched1.toInt(&ok,10);
        }

    if (match2.hasMatch()) {
        bool ok;
        QString matched2 = match2.captured(0);
        matched2Number = matched2.toInt(&ok,10);
        }

    return matched1Number <= matched2Number;
}


