#ifndef IMAGEINSPECTIONMODEL_H
#define IMAGEINSPECTIONMODEL_H
#include <QString>
#include <QStringList>
#include <QMap>
#include <QDir>
#include <QDirIterator>
#include <QRegularExpression>


class ImageInspectionModel {


private:
    QMap<QString, QStringList> m_trainDataset;
    QMap<QString, QStringList> m_validationNewData;
    QMap<QString, QStringList> m_trainNewData;
    QMap<QString, QStringList> m_validationDataset;

public:
    void loadDataSet(const QString &trainingPath, const QString &validationPath);
    void loadNewData(const QString &path, int split);
    void mergeDataSets(const QString &trainingPath, const QString &validationPath);
    void removeImage(int selectionIndex, QMap<QString, QList<int>> removedImages);
    const QMap<QString, QStringList> &getValidationDataset() const;
    const QMap<QString, QStringList> &getTrainDataset() const;
    const QMap<QString, QStringList> &getValidationNewData() const;
    const QMap<QString, QStringList> &getTrainNewData() const;


private:
    QStringList readLabeledFolder(QDir labeledFolder);
    void insertLabeledImagePaths(QMap<QString, QStringList> *insertTarget, QString labeledImagePath);
    void removeImageWithIndex(QMap<QString, QStringList> *removeTarget, QMap<QString, QList<int>> removedImages);
    void mergeMap(QMap<QString, QStringList> *mergeIn, QMap<QString, QStringList> mergeFrom);
    void moveFile(const QString &imagePath, const QString &label, const QString &trainOrValidate, int fileNumber);
    int getFreeImageNumber(const QStringList &paths, const QString &label);
    static bool compareNames(const QString& s1,const QString& s2);

};


#endif //IMAGEINSPECTIONMODEL_H
