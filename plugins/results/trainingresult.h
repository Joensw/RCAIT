#ifndef TRAININGRESULT_H
#define TRAININGRESULT_H


#include <QVector>
#include <QAbstractTableModel>
#include <confusionmatrix.h>
#include <accuracycurve.h>
#include <projectmanager.h>
#include "result.h"

class TrainingResult : public Result {
private:
    QStringList m_mostMisclassifiedImages;
    QMap<int, QPair<double, double>> m_accuracyCurveData;
    QStringList m_classLabels;
    QList<int> m_confusionMatrixValues;
    AccuracyCurve *m_accCurve;
    ConfusionMatrix *m_confusionMatrix;
    double m_top1Accuracy;
    double m_top5Accuracy;

public:
    TrainingResult(const QMap<int, QPair<double, double>> &accuracyCurveData,
                   const QStringList &classLabels, const QList<int> &confusionMatrixValues,
                   QStringList mostMisclassifiedImages, double top1Accuracy, double top5Accuracy,
                   const QStringList &additionalResults = {});

    [[nodiscard]] ConfusionMatrix *getConfusionMatrix() const;

    [[nodiscard]] AccuracyCurve *getAccuracyCurve();

    [[nodiscard]] double getTop1Accuracy() const;

    [[nodiscard]] double getTop5Accuracy() const;

    [[nodiscard]] QStringList getMostMisclassifiedImages() const;

    [[nodiscard]] const QMap<int, QPair<double, double>> &getAccuracyCurveData() const;

    [[nodiscard]] const QStringList &getClassLabels() const;

    [[nodiscard]] const QList<int> &getConfusionMatrixValues() const;

};


#endif //TRAININGRESULT_H
