#ifndef RCAIT_TRAININGRESULT_H
#define RCAIT_TRAININGRESULT_H


#include <QVector>
#include <QAbstractTableModel>
#include "Result.h"

class TrainingResult : public Result{
private:
    //TODO: Pointer?
    QAbstractTableModel* confusionMatrix;
    QMap<int, QVector<double>> lossCurve;
    double top1Accuracy;
    double top5Accuracy;

public:
    TrainingResult(QList<QImage> additionalResult, QAbstractTableModel *confusionMatrix,
                   QMap<int, QVector<double>> lossCurve, double top1Accuracy, double top5Accuracy,
                   QList<QImage> additionalResults);
    QAbstractTableModel* getConfusionMatrix();
    QMap<int, QVector<double>> getLossCurve();
    double getTop1Accuracy();
    double getTop5Accuracy();
};


#endif //RCAIT_TRAININGRESULT_H
