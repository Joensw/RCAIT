#ifndef RCAIT_IMAGEINSPECTIONMODEL_H
#define RCAIT_IMAGEINSPECTIONMODEL_H
#include <QString>
#include <QStringList>
#include <QMap>
#include <QDir>
#include <QDirIterator>
class ImageInspectionModel {


public:
    const QMap<QString, QStringList> &getValidationDataset() const;

    const QMap<QString, QStringList> &getTrainDataset() const;

    const QMap<QString, QStringList> &getValidationNewData() const;

    const QMap<QString, QStringList> &getTrainNewData() const;

private:
    QMap<QString, QStringList> m_trainDataset;
    QMap<QString, QStringList> m_validationNewData;
    QMap<QString, QStringList> m_trainNewData;
    QMap<QString, QStringList> m_validationDataset;
    QString m_newDataPath;
    QString m_DataPath;

public:
    //ToDo: Refactor out validate and train folders to projectmanager and write getter functions
    const QString VALIDATION_FOLDER = "Validate";
    const QString TRAIN_FOLDER = "Train";
    void loadDataSet(QString path);
    void loadNewData(QString path, int split);
    void mergeDataSets();
    void removeImage(int selectionIndex, QMap<QString, QList<int>> removedImages);

private:
    QStringList readLabeledFolder(QDir labeledFolder);
    void insertLabeledImagePaths(QMap<QString, QStringList> *insertTarget, QString labeledImagePath);
    void removeImageWithIndex(QMap<QString, QStringList> *removeTarget, QMap<QString, QList<int>> removedImages);
    void mergeMap(QMap<QString, QStringList> *mergeIn, QMap<QString, QStringList> mergeFrom);
    void removeFile(QString imagePath, QString label, QString trainOrValidate);

};


#endif //RCAIT_IMAGEINSPECTIONMODEL_H
