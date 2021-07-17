#include "imageinspectionmodel.h"

void ImageInspectionModel::loadDataSet(QString path) {
    //reset maps
    m_trainDataset.clear();
    m_validationDataset.clear();

    //add items
    insertLabeledImagePaths(&m_trainDataset,path + "/" + TRAIN_FOLDER);
    insertLabeledImagePaths(&m_validationDataset,path + "/" + VALIDATION_FOLDER);


}

void ImageInspectionModel::mergeDataSets() {



}

void ImageInspectionModel::removeImage(int selectionIndex, int imgIndex) {
    switch(selectionIndex){
        case 0: removeImageWithIndex(&m_validationDataset,imgIndex);
        case 1: removeImageWithIndex(&m_trainDataset,imgIndex);
        case 2: removeImageWithIndex(&m_validationNewData,imgIndex);
        case 3: removeImageWithIndex(&m_trainNewData,imgIndex);
    }

}

void ImageInspectionModel::loadNewData(QString path) {
    //reset maps
    m_trainNewData.clear();
    m_validationNewData.clear();

    //add items
    insertLabeledImagePaths(&m_trainNewData,path + TRAIN_FOLDER);
    insertLabeledImagePaths(&m_validationNewData,path + VALIDATION_FOLDER);


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

    QDirIterator it(labeledImagePath);
    while (it.hasNext()) {
        QDir dir = it.next();
        //skip over filesystem specific folders
        if(dir.dirName() == "." || dir.dirName() == ".."){
            continue;
        }
        insertTarget->insert(dir.dirName(),readLabeledFolder(dir));
    }
}

void ImageInspectionModel::removeImageWithIndex(QMap<QString, QStringList> *removeTarget, int index) {
    //ToDo: Implement when view is defined
    //https://doc.qt.io/qt-5/qmap-key-iterator.html
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
