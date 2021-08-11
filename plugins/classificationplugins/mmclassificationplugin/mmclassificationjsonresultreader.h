#ifndef MMCLASSIFICATIONJSONRESULTREADER_H
#define MMCLASSIFICATIONJSONRESULTREADER_H

#include <QObject>

class MMClassificationJsonResultReader
{
public:
    MMClassificationJsonResultReader();

    QVector<int> readConfusionMatrixFromJsonFile(QString filePath);
    QMap<int, QPair<double, double>> getAccuracyCurve(QString logFilePath);
    QPair<double, double> readTopValuesFromJson(QString filePath);
    QStringList generateMostMissclassifiedImages(int requiredNumber, QString pathToValTxt, QString pathToJsonResult);
    QMap<QString, QList<double>> readConfidenceScores(QString filePath, QStringList imageFileNames);

};

#endif // MMCLASSIFICATIONJSONRESULTREADER_H
