#ifndef RCAIT_TRAININGRESULT_H
#define RCAIT_TRAININGRESULT_H


#include <QVector>
#include <QAbstractTableModel>
#include "result.h"

class TrainingResult : public Result {
private:
    QList<QImage> m_mostMisclassifiedImages;
    QMap<int, QPair<double,double>> m_lossCurve;
    QStringList m_classLabels;
    QAbstractTableModel *m_confusionMatrix;
    double m_top1Accuracy;
    double m_top5Accuracy;

public:
    TrainingResult(QMap<int, QPair<double,double>> lossCurve,
                   QAbstractTableModel *confusionMatrix, const QStringList& classLabels, QList<QImage> mostMisclassifiedImages,
                   double top1Accuracy, double top5Accuracy, QList<QImage> additionalResults);

    QAbstractTableModel *getConfusionMatrix();

    QMap<int, QPair<double,double>> getLossCurve();

    [[nodiscard]] double getTop1Accuracy() const;

    [[nodiscard]] double getTop5Accuracy() const;

    [[nodiscard]] const QList<QImage> &getMostMisclassifiedImages() const;

    [[nodiscard]] const QStringList &getClassLabels() const;
};


#endif //RCAIT_TRAININGRESULT_H
