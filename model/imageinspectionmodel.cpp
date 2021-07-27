#include "imageinspectionmodel.h"

void ImageInspectionModel::loadDataSet(QString path) {
    //reset maps
    m_DataPath = path;
    m_trainDataset.clear();
    m_validationDataset.clear();

    //add items
    insertLabeledImagePaths(&m_trainDataset,path + "/" + TRAIN_FOLDER);
    insertLabeledImagePaths(&m_validationDataset,path + "/" + VALIDATION_FOLDER);

}

void ImageInspectionModel::mergeDataSets() {
    mergeMap(&m_trainDataset, m_trainNewData);
    mergeMap(&m_validationDataset,m_validationNewData);
    //move files since we can do it here for free before cleaning up the data structures
    foreach(QString label, m_trainNewData.keys()){
        for(QString& imagePath : m_trainNewData.value(label)){
            removeFile(imagePath,label ,TRAIN_FOLDER);
        }
    }

    foreach(QString label, m_validationNewData.keys()){
        for(QString& imagePath : m_validationNewData.value(label)){
            removeFile(imagePath,label ,VALIDATION_FOLDER);
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

void ImageInspectionModel::loadNewData(QString path, int split) {
    m_newDataPath = path;
    //reset maps because new data is coming
    m_trainNewData.clear();
    m_validationNewData.clear();

    //create a temporary map to calculate split for train and validate
    QMap<QString, QStringList> allData;
    insertLabeledImagePaths(&allData,path);

    foreach(QString key, allData.keys()){
        int dataPoints = allData.value(key).count();
        double splitPerc = (double) split/ (double) 100;
        double splitPosDbl = (double) dataPoints * splitPerc;
        //we use floor and use the split for train images so validation is not empty except if 100 is chosen
        int splitPosInt = floor(splitPosDbl);

        QStringList data = allData.value(key);
        m_trainNewData.insert(key,QStringList(data.mid(0,splitPosInt - 1)));
        if(!(splitPosInt == data.count())){
             m_validationNewData.insert(key,QStringList(data.mid(splitPosInt - 1)));
        }
        m_validationNewData.insert(key,QStringList());
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

void ImageInspectionModel::removeFile(QString imagePath,QString label, QString trainOrValidate) {
    QFile file(imagePath);
    QFileInfo fileInfo(file);
    QDir folder(fileInfo.absoluteDir());
    QString filename(fileInfo.fileName());
    QString newPath = m_DataPath  + "/" + trainOrValidate + "/" + label;
    if(!QDir(newPath).exists()) {
        QDir().mkdir(newPath);
    }
    QString newFileName = newPath + "/" + filename;
    QFile destFile(newFileName);
    if(destFile.exists()){
        destFile.remove();
    }
    if(file.rename(newFileName)){
        qDebug() << "check if file is already in target folder";
    }
    imagePath = newFileName;
    if(folder.isEmpty()){
        folder.removeRecursively();
    }

}


