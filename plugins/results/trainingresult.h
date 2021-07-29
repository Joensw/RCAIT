#ifndef TRAININGRESULT_H
#define TRAININGRESULT_H


#include <QVector>
#include <QAbstractTableModel>
#include <confusionmatrix.h>
#include <accuracycurve.h>
#include "result.h"

class TrainingResult : public Result {
private:
    QList<QImage> m_mostMisclassifiedImages;
    AccuracyCurve *m_accCurve;
    ConfusionMatrix *m_confusionMatrix;
    double m_top1Accuracy;
    double m_top5Accuracy;

public:
    TrainingResult(AccuracyCurve *accCurve, ConfusionMatrix *confusionMatrix, QList<QImage> mostMisclassifiedImages,
                   double top1Accuracy, double top5Accuracy, const QList<QImage> &additionalResults);

    [[nodiscard]] ConfusionMatrix *getConfusionMatrix() const;

    [[nodiscard]] AccuracyCurve *getAccuracyCurve();

    [[nodiscard]] double getTop1Accuracy() const;

    [[nodiscard]] double getTop5Accuracy() const;

    [[nodiscard]] QList<QImage> getMostMisclassifiedImages() const;

};


#endif //TRAININGRESULT_H
