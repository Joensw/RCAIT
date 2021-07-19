#include "trainingresult.h"

#include <utility>

TrainingResult::TrainingResult(LossCurve *lossCurve, ConfusionMatrix *confusionMatrix,
                               QList<QImage> mostMisclassifiedImages,
                               double top1Accuracy, double top5Accuracy, const QList<QImage> &additionalResults)
        : Result(additionalResults) {
    m_lossCurve = lossCurve;
    m_confusionMatrix = confusionMatrix;
    m_mostMisclassifiedImages = std::move(mostMisclassifiedImages);
    m_top1Accuracy = top1Accuracy;
    m_top5Accuracy = top5Accuracy;
}

LossCurve *TrainingResult::getLossCurve() {
    return m_lossCurve;
}

ConfusionMatrix *TrainingResult::getConfusionMatrix() const {
    return m_confusionMatrix;
}

QList<QImage> TrainingResult::getMostMisclassifiedImages() const {
    return m_mostMisclassifiedImages;
}

double TrainingResult::getTop1Accuracy() const {
    return m_top1Accuracy;
}

double TrainingResult::getTop5Accuracy() const {
    return m_top5Accuracy;
}
