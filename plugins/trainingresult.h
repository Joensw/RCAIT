#ifndef TRAININGRESULT_H
#define TRAININGRESULT_H

#include "result.h"

#include <QMap>
#include <QVector>

class TrainingResult : public Result
{
public:
    //TODO: proper type for confusion Matrix
    TrainingResult(int* confusionMatrix, QMap<int, QVector<double>> lossCurve, double top1Accuracy, double top5Accuracy, QList<QImage> additionalResults);
    int* getConfusionMatrix();
    QMap<int, QVector<double>> getLossCurve();
    double getTop1Accuracy();
    double getTop5Accuracy();

private:
    int* confusionMatrix;
    QMap<int, QVector<double>> lossCurve;
    double top1Accuracy;
    double top5Accuracy;
};

#endif // TRAININGRESULT_H
