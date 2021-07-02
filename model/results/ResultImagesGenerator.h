#ifndef RCAIT_RESULTIMAGESGENERATOR_H
#define RCAIT_RESULTIMAGESGENERATOR_H


#include <plugins/results/TrainingResult.h>
#include <plugins/results/ClassificationResult.h>

class ResultImagesGenerator {
public:
    ResultImagesGenerator();
    //Todo: QImages Lists are weird
    QList<QImage> generateTrainingResultImages(TrainingResult* result);
    QList<QImage> generateClassificationResultImages(ClassificationResult* result);

private:
    QImage generateConfusionMatrixImage(QAbstractTableModel matrix, QStringList labels);
    QImage generateLossCurveImage(QMap<int, QVector<double>>);
    //Todo: Weird stuff below
    QImage generateAccuracyImage(double top1 , double top5);
    QImage generateClassificationTableImage(QMap<QString, QVector<double>> table, QVector<QString> labels);
};


#endif //RCAIT_RESULTIMAGESGENERATOR_H
