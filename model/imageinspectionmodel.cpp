#include "imageinspectionmodel.h"

void imageinspectionmodel::loadDataSet(QString path) {
    //reset maps
    m_trainDataset.clear();
    m_validationDataset.clear();

    //add items
    insertLabeledImagePaths(m_trainDataset,path + TRAIN_FOLDER);
    insertLabeledImagePaths(m_validationDataset,path + VALIDATION_FOLDER);


}

void imageinspectionmodel::mergeDataSets() {



}

void imageinspectionmodel::removeImage(int selectionIndex, int imgIndex) {
    switch(selectionIndex){
        case 0: removeImageWithIndex(m_validationDataset,imgIndex);
        case 1: removeImageWithIndex(m_trainDataset,imgIndex);
        case 2: removeImageWithIndex(m_validationNewData,imgIndex);
        case 3: removeImageWithIndex(m_trainNewData,imgIndex);
    }

}

void imageinspectionmodel::loadNewData(QString path) {
    //reset maps
    m_trainNewData.clear();
    m_validationNewData.clear();

    //add items
    insertLabeledImagePaths(m_trainNewData,path + TRAIN_FOLDER);
    insertLabeledImagePaths(m_validationNewData,path + VALIDATION_FOLDER);


}

QStringList imageinspectionmodel::readLabeledFolder(QDir labeledFolder) {
    QStringList images = labeledFolder.entryList(QStringList(),QDir::Files);
    return images;
}

void imageinspectionmodel::insertLabeledImagePaths(QMap<QString, QStringList> insertTarget, QString labeledImagePath){

    QDirIterator it(labeledImagePath);
    while (it.hasNext()) {
        QDir dir = it.next();
        insertTarget.insert(dir.dirName(),readLabeledFolder(dir));
    }
}

void imageinspectionmodel::removeImageWithIndex(QMap<QString, QStringList>, int index) {
    //ToDo: Implement when view is defined
    //https://doc.qt.io/qt-5/qmap-key-iterator.html
}
