#ifndef RCAIT_TRAININGRESULT_H
#define RCAIT_TRAININGRESULT_H


#include <QVector>
#include <QAbstractTableModel>
#include <confusionmatrix.h>
#include "result.h"

class TrainingResult : public Result {
private:
    QList<QImage> m_mostMisclassifiedImages;
    QMap<int, QPair<double,double>> m_lossCurveData;
    ConfusionMatrix *m_confusionMatrix;
    double m_top1Accuracy;
    double m_top5Accuracy;

public:
    TrainingResult(QMap<int, QPair<double,double>> lossCurveData,
                   ConfusionMatrix *confusionMatrix, QList<QImage> mostMisclassifiedImages,
                   double top1Accuracy, double top5Accuracy, QList<QImage> additionalResults);

    [[nodiscard]] ConfusionMatrix *getConfusionMatrix() const;

    QMap<int, QPair<double,double>> getLossCurveData();

    [[nodiscard]] double getTop1Accuracy() const;

    [[nodiscard]] double getTop5Accuracy() const;

    [[nodiscard]] const QList<QImage> &getMostMisclassifiedImages() const;

};


#endif //RCAIT_TRAININGRESULT_H
