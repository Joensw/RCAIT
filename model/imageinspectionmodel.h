/**
 * @file imageinspectionmodel.h
 *
 * @brief fuctions for managing a classification dataset on disk
 *
 * @author Sascha Rolinger
 */
#ifndef IMAGEINSPECTIONMODEL_H
#define IMAGEINSPECTIONMODEL_H
#include <QString>
#include <QStringList>
#include <QMap>
#include <QDir>
#include <QDirIterator>
#include <QRegularExpression>

/**
 * @brief The ImageInspectionModel class
 */
class ImageInspectionModel final {


private:
    QMap<QString, QStringList> m_trainDataset;
    QMap<QString, QStringList> m_validationNewData;
    QMap<QString, QStringList> m_trainNewData;
    QMap<QString, QStringList> m_validationDataset;
    static constexpr auto REGEX_NUMBER = "\\d+";
    static inline const QRegularExpression REGEX = QRegularExpression(REGEX_NUMBER);

public:
    /**
     * @brief ImageInspectionModel constructor
     */
    ImageInspectionModel();

    /**
     * @brief loadDataSet loads validation and training data from the given folders. Format in the training/validation folder has to be e.g.
     * /training
     *  /Label1
     *      /image1.jpg
     *      /image2.jpg
     *  /Label2
     *      /image1.jpg
     *
     * @param trainingPath the path to training data
     * @param validationPath the path to validation data
     */
    void loadDataSet(const QString &trainingPath, const QString &validationPath);
    /**
     * @brief loadNewData loads new data from a folder with label subfolders and images there in and splits them by the given percentage
     * @param path to the folder with the labeled subfolders
     * @param split as integer (100 = 100%). #validation images = #total images * split (%), and #training images is the rest
     */
    void loadNewData(const QString &path, int split);

    /**
     * @brief mergeDataSets merges the loaded NewData and the dataset specified by the arguments. The files will be moved on the filesystem.
     * @param trainingPath the path to the training folder
     * @param validationPath the path to the validation folder
     */
    void mergeDataSets(const QString &trainingPath, const QString &validationPath);

    /**
     * @brief removeImage removes images from ValidationNewData (0), TrainNewData (1), ValidationDataset (2), TrainDataset (3) by label and index in the labeled folder.
     * @param selectionIndex index of the list where the data is to be deleted
     * @param removedImages label and indices of the images in the labeled folder
     */
    void removeImage(int selectionIndex, const QMap<QString, QList<int>> &removedImages);

    /**
     * @brief getValidationDataset get the validation dataset used in the model
     * @return Label as Key and QStringList as paths to images for the given part of the dataset
     */
    [[nodiscard]] const QMap<QString, QStringList> &getValidationDataset() const;

    /**
     * @brief getTrainDataset get the training dataset used in the model
     * @return Label as Key and QStringList as paths to images for the given part of the dataset
     */
    [[nodiscard]] const QMap<QString, QStringList> &getTrainDataset() const;

    /**
     * @brief getValidationNewData get the new validation data used in the model
     * @return Label as Key and QStringList as paths to images for the given part of the dataset
     */
    [[nodiscard]] const QMap<QString, QStringList> &getValidationNewData() const;

    /**
     * @brief getTrainNewData get the new training data used in the model
     * @return Label as Key and QStringList as paths to images for the given part of the dataset
     */
    [[nodiscard]] const QMap<QString, QStringList> &getTrainNewData() const;


private:
    static QStringList readLabeledFolder(const QDir &labeledFolder);

    static void insertLabeledImagePaths(QMap<QString, QStringList> &insertTarget, const QString &labeledImagePath);
    static void removeImageWithIndex(QMap<QString, QStringList> &removeTarget, const QMap<QString, QList<int>>& removedImages);
    static void mergeMap(const QMap<QString, QStringList> &mergeIn, const QMap<QString, QStringList>& mergeFrom);
    static void moveFile(const QString &imagePath, const QString &label, const QString &trainOrValidate, int fileNumber);
    static int getFreeImageNumber(const QStringList &paths, const QString &label);
    static bool compareNames(const QString& s1,const QString& s2);

};


#endif //IMAGEINSPECTIONMODEL_H
