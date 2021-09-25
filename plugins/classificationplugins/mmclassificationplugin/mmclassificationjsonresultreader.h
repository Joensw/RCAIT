#ifndef MMCLASSIFICATIONJSONRESULTREADER_H
#define MMCLASSIFICATIONJSONRESULTREADER_H

#include <QObject>

/**
 * @brief The MMClassificationJsonResultReader class extracts the relevant data from the json and txt files generated by the scripts from MMClassification
 */
class MMClassificationJsonResultReader
{
public:

    /**
     * @brief readConfusionMatrixFromJsonFile reads a json file containing a confusion matrix
     * @param filePath the path to json file to read
     * @return the confusionmatrix is a square matrix of dimension number of labels/classes and lines are one behind the other,
     *         returns an empty QVector on error
     */
    QVector<int> readConfusionMatrixFromJsonFile(const QString &filePath);

    /**
     * @brief getAccuracyCurve reads the .log.json file and returns the accuracy curve
     * @param logFilePath the path of the .log.json file generated by MMClassification
     * @return the accuracy curve containing the top-1 train and top-1 validation values per iteration in step of evaluation frequency,
     *         returns an empty QMap on error
     */
    QMap<int, QPair<double, double>> getAccuracyCurve(QString logFilePath);

    /**
     * @brief readTopValuesFromJson reads the top-1 and top-5 values from the corresponding json result file
     * @param filePath the path of the accuracy result file generated by the test method from MMClassification with the accuracy metric argument
     * @return the top-1 value and then the top-5 value, returns an empty QPair on error
     */
    QPair<double, double> readTopValuesFromJson(QString filePath);

    /**
     * @brief generateMostMissclassifiedImages calculates requiredNumber many most missclassified images based on the validation dataset
     * @param requiredNumber the number of most missclassified images to return
     * @param pathToValTxt the path of the val.txt annotation file generated by a training with MMClassification
     * @param pathToJsonResult the path to a json file containing the classification results with the validation dataset, made by not specifying a specific metric
     * @return requiredNumber many most missclassified images, returns an empty QStringList on error
     */
    QStringList generateMostMissclassifiedImages(int requiredNumber, const QString &pathToValTxt, const QString &pathToJsonResult);

    /**
     * @brief readConfidenceScores reads the confidence scores of the appropiate json file
     * @param filePath the path of the appropiate json file containing the confidence scores
     * @param imageFileNames a alphabetically (with ascending numbers) sorted list of file names (see val.txt or MMClassificatoin for further distinction)
     * @return a map assigning each file name its correspoding confidence scores, returns an empty QMap on error
     */
    QMap<QString, QList<double>> readConfidenceScores(QString filePath, QStringList imageFileNames);

    /**
     * @brief readAnnotationFile reads the specified annotation file and extracts its content
     * @param annotationFilePath the annotation file is a .txt file created by MMClassification
     * @return returns a ordered sequence of filenames and a sequence of numbers between 0 and number of classes -1, indicating its class
     */
    QPair<QVector<QString>, QVector<int>> readAnnotationFile(const QString &annotationFilePath);

};

#endif // MMCLASSIFICATIONJSONRESULTREADER_H
