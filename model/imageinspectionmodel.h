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
    void removeImage(int selectionIndex, const QMap<QString, QList<int>>& removedImages);
    const QMap<QString, QStringList> &getValidationDataset() const;
    const QMap<QString, QStringList> &getTrainDataset() const;
    const QMap<QString, QStringList> &getValidationNewData() const;
    const QMap<QString, QStringList> &getTrainNewData() const;


private:
    static QStringList readLabeledFolder(const QDir& labeledFolder);
    static void insertLabeledImagePaths(QMap<QString, QStringList> &insertTarget, const QString& labeledImagePath);
    static void removeImageWithIndex(const QMap<QString, QStringList> &removeTarget, const QMap<QString, QList<int>>& removedImages);
    static void mergeMap(const QMap<QString, QStringList> &mergeIn, const QMap<QString, QStringList>& mergeFrom);
    static void moveFile(const QString &imagePath, const QString &label, const QString &trainOrValidate, int fileNumber);
    static int getFreeImageNumber(const QStringList &paths, const QString &label);
    static bool compareNames(const QString& s1,const QString& s2);

};


#endif //IMAGEINSPECTIONMODEL_H
