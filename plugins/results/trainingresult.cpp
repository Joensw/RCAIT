#include "trainingresult.h"

#include <utility>

TrainingResult::TrainingResult(AccuracyCurve *accCurve, ConfusionMatrix *confusionMatrix,
                               QStringList mostMisclassifiedImages,
                               double top1Accuracy, double top5Accuracy, const QStringList &additionalResults)
        : Result(additionalResults),
          m_accCurve(accCurve),
          m_confusionMatrix(confusionMatrix),
          m_top1Accuracy(top1Accuracy),
          m_top5Accuracy(top5Accuracy) {

    m_mostMisclassifiedImages = std::move(mostMisclassifiedImages);
}

AccuracyCurve *TrainingResult::getAccuracyCurve() {
    return m_accCurve;
}

ConfusionMatrix *TrainingResult::getConfusionMatrix() const {
    return m_confusionMatrix;
}

QStringList TrainingResult::getMostMisclassifiedImages() const {
    return m_mostMisclassifiedImages;
}

double TrainingResult::getTop1Accuracy() const {
    return m_top1Accuracy;
}

double TrainingResult::getTop5Accuracy() const {
    return m_top5Accuracy;
}
